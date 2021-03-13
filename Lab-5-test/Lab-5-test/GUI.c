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
	CLEAR;
	pthread_mutex_lock(&stateMutex);
	switch (lights)
	{
		case RED:
			printf("NorthLight: Red North: %d,	 Bridge: %d,	South: %d SouthLight: Red\n", queues[1], queues[0], queues[2]);
			break;
		
		case NORTHGREEN:
			printf("NorthLight: Green North: %d,	 Bridge: %d,	 South: %d SouthLight: Red\n", queues[1], queues[0], queues[2]);
			break;
			
		case SOUTHGREEN:
			printf("NorthLight: Red North: %d,	 Bridge: %d,	South: %d SouthLight: Green\n", queues[1], queues[0], queues[2]);
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