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

void *keyboardInput(void *arg);

int main(void)
{
	CLEAR;
	printf("Started the Simulator\n");
	
	initState();
	initGUI();
	
	pthread_t keyboardInputThread;
	pthread_t arrivalThread;
	pthread_t ioThread;
	pthread_t bridgeEnterThread;
	
	if (pthread_create(&keyboardInputThread, NULL, keyboardInput, NULL)){
		printf("Failed to create keyboard input thread");
	}
	if (pthread_create(&arrivalThread, NULL, arrivalWait, NULL)){
		printf("Failed to create arrival thread");
	}
	if (pthread_create(&ioThread, NULL, readSerialPort, NULL)){
		printf("Failed to create read serial port thread");
	}
	if (pthread_create(&bridgeEnterThread, NULL, bridgeEnter, NULL)){
		printf("Failed to create bridge enter thread");
	}
	
	pthread_join(keyboardInputThread, NULL);
}

void *keyboardInput(void *arg){
	char ch;
	
	while ( (ch = getchar()) != 'e'){
		if(ch == 's'){
			pthread_mutex_lock(&stateMutex);
			arrivalDir = SOUTH;
			pthread_mutex_unlock(&stateMutex);
			sem_post(&arrivalSem);
		}
		else if(ch == 'n'){
			pthread_mutex_lock(&stateMutex);
			arrivalDir = NORTH;
			pthread_mutex_unlock(&stateMutex);
			sem_post(&arrivalSem);
		}
	}
	print();
	printf("Exits the Simulator\n");
}


