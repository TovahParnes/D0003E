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
	TIMSK1 = (1<<OCIE1B) | TIMSK1;
	// Turn on OC1A compare match
	TCCR1A = (1<<COM1A0) | TCCR1A;
	// Set timer to clear on timer compare (CTC) and timer prescaling factor 1024 
	TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS12) | (1<<CS10) | TCCR1B;
		
	TCNT1 = 0;
	OCR1A = 0x10;
}

static void enqueue(thread p, thread *queue) {
    p->next = NULL;
    if (*queue == NULL) {
        *queue = p;
    } else {
        thread q = *queue;
        while (q->next)
            q = q->next;
        q->next = p;
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

void yield(void) {
	ENABLE();
	enqueue(current, &readyQ);
	dispatch(dequeue(&readyQ));
	DISABLE();
}

ISR(PCINT1_vect){
	bool down = false;
	bool pressed = false;
	if ((( PINB & 1<<PB7) == 0)){
		down = true;
	}
	else{
		down = false;
		pressed = false;
	} 
	
	if (!pressed && down){
		yield();
		pressed = true;
	}
	
	
}

ISR (TIMER1_COMPA_vect){
		yield();
}

void lock(mutex *m) {

}

void unlock(mutex *m) {

}
