#include <setjmp.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "tinythreads.h"

#define NULL            0
#define DISABLE()       cli()
#define ENABLE()        sei()
#define STACKSIZE       80
#define NTHREADS        4
#define SETSTACK(buf,a) *((unsigned int *)(buf)+8) = (unsigned int)(a) + STACKSIZE - 4; \
                        *((unsigned int *)(buf)+9) = (unsigned int)(a) + STACKSIZE - 4
						

struct thread_block {
    void (*function)(int);   // code to run
    int arg;                 // argument to the above
    thread next;             // for use in linked lists
    jmp_buf context;         // machine state
    char stack[STACKSIZE];   // execution stack space
};

struct thread_block threads[NTHREADS];

struct thread_block initp;

thread freeQ   = threads;
thread readyQ  = NULL;
thread current = &initp;

int initialized = 0;

mutex mutexButton = MUTEX_INIT;
mutex mutexBlink = MUTEX_INIT;

static void initialize(void) {
    int i;
    for (i=0; i<NTHREADS-1; i++){
        threads[i].next = &threads[i+1];
	}
    threads[NTHREADS-1].next = NULL;


    initialized = 1;
	
	// Initialize for butterfly joystick
	EIMSK = (1<<PCIE1) | EIMSK;
	PCMSK1 = (1<<PCINT15) | PCMSK1;
	PORTB = (1<<PB7) | PORTB;
	
	// Initialize for timer 
	
	// Enable timer output compare A interrupts 
	TIMSK1 = (1<<OCIE1A) | TIMSK1;
	// Turn on OC1A compare match
	TCCR1A = (1<<COM1A0) | (1<<COM1A1) | TCCR1A;
	// Set timer to clear on timer compare (CTC) and timer prescaling factor 1024 
	TCCR1B = (1<<WGM12) | (1<<CS12) | (1<<CS10) | TCCR1B;
	
	// 20 intervals of 50 ms per second 
	// 1 second = 8 000 000 / 1024 = 7812.5 
	// 1 second divided by 2 intervals = 7812.5/2 = 3906,25 = 0xF42
	OCR1A = 0xF42;	
	TCNT1 = 0x0;
	
}

static void enqueue(thread p, thread *queue) {
    p->next = NULL;
    if (*queue == NULL) {
        *queue = p;
    } else {
        thread q = *queue;
		p->next = q;
        *queue = p;
    }
}

static thread dequeue(thread *queue) {
    thread p = *queue;
    if (*queue) {
        *queue = (*queue)->next;
    } else {
        // Empty queue, kernel panic!!!
        while (1) ;  // not much else to do...
    }
    return p;
}

static void dispatch(thread next) {
    if (setjmp(current->context) == 0) {
        current = next;
        longjmp(next->context,1);
    }
}

void spawn(void (* function)(int), int arg) {
    thread newp;

    DISABLE();
    if (!initialized) initialize();

    newp = dequeue(&freeQ);
    newp->function = function;
    newp->arg = arg;
    newp->next = NULL;
    if (setjmp(newp->context) == 1) {
        ENABLE();
        current->function(current->arg);
        DISABLE();
        enqueue(current, &freeQ);
        dispatch(dequeue(&readyQ));
    }
    SETSTACK(&newp->context, &newp->stack);

    enqueue(newp, &readyQ);
	ENABLE();
}

ISR(PCINT1_vect){
	unlock(&mutexButton);
}

ISR(TIMER1_COMPA_vect){
	unlock(&mutexBlink);
}

void lock(mutex *m) {
	DISABLE();
	//if the mutex is locked, add the thread to the wait queue and change to the next thread in the ready queue
	if (m->locked){
		enqueue(current, &(m->waitQ));
		dispatch(dequeue(&readyQ));
	}
	//If the mutex isn't locked, lock it, and add the current thread to the ready queue
	else {
		enqueue (current, &readyQ);
		m->locked = 1;
	}
	ENABLE();
	
}

void unlock(mutex *m) {
	DISABLE();
	//If the wait queue isn't empty, add the current thread to the ready queue
	if (m->waitQ != NULL){
		enqueue(m->waitQ, &readyQ);
	}
	//Go to the next thread in the ready queue
	dispatch(dequeue(&readyQ));
	ENABLE();
	
}

/*
The mutex adds the threads to a waiting queue if they cannot continue, but can still change between threads.
The ENABLE/DISABLE turns off the ability to cause interruptions, ex timer or button.
*/