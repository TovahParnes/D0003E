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

#include "GUI.h"
#include "state.h"

void *keyboardInput(void *arg);

int main(void)
{
	printf("Start the Simulator\n");
	
	pthread_t keyboardInputThread;
	pthread_t arrivalThread;
	
	initGUI();
	//initState();
	
	if (pthread_create(&keyboardInputThread, NULL, keyboardInput, NULL)){
		printf("Failed to create keyboard input thread");
	}
	/*if (pthread_create(&arrivalThread, NULL, arrivalWait, NULL)){
		printf("Failed to create keyboard input thread");
	}*/
	
	while (1)
	{
	}
	
	//pthread_join(keyboardInputThread, NULL);
}

void *keyboardInput(void *arg){
	char ch;
	
	while ( (ch = getchar()) != 'e'){
		if(ch == 's'){
			sem_post(&arrivalSem);
			carsSouth++;
			printf("Cars South %d\n", carsSouth);
			
		}
		else if(ch == 'n'){
			printf("pressed n\n");
			CLEAR;
		}
		
	}
	printf("Exits the Simulator\n");
}


