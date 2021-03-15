/*
 * GUI.c
 *
 * Created: 2021-03-12 10:44:56
 *  Author: adahed-8
 */ 

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include "GUI.h"
#include "state.h"


void print(void){
	pthread_mutex_lock(&stateMutex);
	
	switch (lights)
	{
		case RED:
			CLEAR;
			printf("North:  %d RED,     Bridge: %d,     South: %d RED\n", queues[1], queues[0], queues[2]);
			printf("\n");
			break;
		
		case NORTHGREEN:
			CLEAR;
			printf("North: %d GREEN,   Bridge: %d,     South: %d RED\n", queues[1], queues[0], queues[2]);
			printf("\n");
			break;
			
		case SOUTHGREEN:
			CLEAR;
			printf("North: %d RED,     Bridge: %d,     South: %d GREEN\n", queues[1], queues[0], queues[2]);
			printf("\n");
			break;
	}
	pthread_mutex_unlock(&stateMutex);
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

void initGUI(void){
	terminalSettings();
}