/*
 * Lab-5-test.c
 *
 * Created: 2021-03-11 10:52:01
 * Author : adahed-8
 */ 

//To run in cygwin:
// gcc main.c -o FILENAME
// ./FILENAME

#include <stdint.h>
#include <pthread.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include "GUI.h"
#include "state.h"

#define CLEAR printf("\x1B[2J");

void *keyboardInput(void *arg);
void *arrivalWait(void *arg);
void arrival(uint64_t dir);
void terminalSettings(void);
void print(void);

uint64_t arrivalDirection;
sem_t arrivalSem;
sem_t stateLoopSem;
pthread_mutex_t stateMutex;
uint64_t queues[3];

static struct termios oldTerminalSettings, prgmTerminalSettings;

int main(void)
{
	printf("Start the Simulator\n");
	
	terminalSettings();
	
	pthread_t keyboardInputThread;
	pthread_t arrivalThread;
	
	sem_init(&arrivalSem, 0, 0);
	
	if (pthread_mutex_init(&stateMutex, NULL) != 0) printf("Failed to create stateMutex");
	
	if (pthread_create(&keyboardInputThread, NULL, keyboardInput, NULL)){
		printf("Failed to create keyboard input thread");
	}
	if (pthread_create(&arrivalThread, NULL, arrivalWait, NULL)){
		printf("Failed to create keyboard input thread");
	}
	
	pthread_join(keyboardInputThread, NULL);
}

void *keyboardInput(void *arg){
	char ch;
	
	while ( (ch = getchar()) != 'e'){
		if(ch == 's'){
			pthread_mutex_lock(&stateMutex);
			arrivalDirection = 2;
			pthread_mutex_unlock(&stateMutex);
			sem_post(&arrivalSem);
		}
		else if(ch == 'n'){
			pthread_mutex_lock(&stateMutex);
			arrivalDirection = 1;
			pthread_mutex_unlock(&stateMutex);
			sem_post(&arrivalSem);
		}
	}
	print();
	printf("Exits the Simulator\n");
}

void *arrivalWait(void *arg) {
	uint64_t directionArg;
	while (1) {
		sem_wait(&arrivalSem);
		printf("arrivalWait\n");
		pthread_mutex_lock(&stateMutex);
		directionArg = arrivalDirection;
		pthread_mutex_unlock(&stateMutex);
		arrival(directionArg);
	}

	return NULL;
}

void arrival(uint64_t dir) {
	printf("Arrival %d\n", dir);
	queues[dir]++;
	print();

	/*
	uint8_t data = (dir == NORTHBOUND) ? 0b0001 : 0b0100;

	pthread_mutex_lock(&ioMutex);
	write(serialFD, &data, 1);
	pthread_mutex_unlock(&ioMutex);

	printf("\x1B[3;0Hserial write: 0x%x", data);
	printf("\x1B[38;0Hstatetry A");
	pthread_mutex_lock(&stateMutex);
	printf("\x1B[38;0Hstatemut A");
	arrivalBuffers[dir]++;
	pthread_mutex_unlock(&stateMutex);
	//if (!pendingEnter && bridgeEmpty) sem_post(&stateLoopSem);
	sigTUIUpdate();
	*/
}

void terminalSettings(void){
	//copy current settings
	tcgetattr(STDIN_FILENO, &prgmTerminalSettings);

	//set new settings
	prgmTerminalSettings.c_lflag &= ~(ICANON) // Disable input buffer until endl or EOF
								 &  ~(ECHO);  // Don't echo back typed keys
	
	//Save new settings
	tcsetattr(STDIN_FILENO, TCSANOW, &prgmTerminalSettings);
}

void print(void){
	CLEAR;
	printf("North: %d, Bridge: %d, South: %d\n", queues[1], queues[0], queues[2]);
}

