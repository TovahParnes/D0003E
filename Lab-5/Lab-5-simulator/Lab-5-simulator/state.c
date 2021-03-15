/*
 * state.c
 *
 * Created: 2021-03-12 10:47:55
 *  Author: adahed-8
 */ 

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>

#include "GUI.h"
#include "state.h"

void initState(void){
	sem_init(&arrivalSem, 0, 0);
	sem_init(&bridgeEnterSem, 0, 0);
	
	if (pthread_mutex_init(&stateMutex, NULL) != 0) printf("Failed to create stateMutex");
	
	if (pthread_mutex_init(&ioMutex, NULL) != 0) printf("Failed to create ioMutex");
	
	//Set up serial port
	serialPort = open("/dev/ttyS0", O_RDWR);

	if (serialPort == -1) printf("Failed to open /dev/ttyS0");
	
	tcgetattr(serialPort, &serialSettings);

	fcntl(serialPort, F_SETFL, O_NONBLOCK);

	//Set port speed
	cfsetospeed(&serialSettings, B9600);
	cfsetispeed(&serialSettings, B9600);
	
	serialSettings.c_cflag &= ~CSIZE; 	// Clear char size
	serialSettings.c_cflag |= CS5;	// set 5 bit char size
	serialSettings.c_cflag &= ~CSTOPB; // 1 stop bit
	serialSettings.c_cflag &= ~PARENB; // no parity
	serialSettings.c_cflag |= CREAD;	// Enable receive
	serialSettings.c_cc[VMIN] =  1; // Read at least 1 char
	
	//Save serial settings
	//tcsetattr(serialPort, TCSANOW, &serialSettings);
	lights = 0;
}


void *arrivalWait(void *arg) {
	uint64_t directionArg;
	while (1) {
		sem_wait(&arrivalSem);
		pthread_mutex_lock(&stateMutex);
		directionArg = arrivalDir;
		pthread_mutex_unlock(&stateMutex);
		arrival(directionArg);
	}

	return NULL;
}

void arrival(uint64_t dir) {
	//write to port
	uint8_t data = (dir == NORTH) ? 0b0001 : 0b0100;
	pthread_mutex_lock(&ioMutex);
	write(serialPort, &data, 1);
	pthread_mutex_unlock(&ioMutex);
	
	//Update queues
	pthread_mutex_lock(&stateMutex);
	queues[dir]++;
	pthread_mutex_unlock(&stateMutex);
	print();
}

void *bridgeEnter(void *arg){
	printf("Started bridge enter thread\n");
	while(1){
		sem_wait(&bridgeEnterSem);
		pthread_t carThread;
		
		if (pthread_create(&carThread, NULL, carOnBridge, NULL)){
			printf("Failed to create car thread");
		}
	}
}

void *carOnBridge(void *arg){
	pthread_mutex_lock(&stateMutex);
	if (queues[lights] > 0)
	{
		//Update queues
		queues[lights]--;
		queues[0]++;
		//Write car enter bridge
		uint8_t data = (lights == NORTHGREEN) ? 0b0010 : 0b1000;
		pthread_mutex_unlock(&stateMutex);
		print();
		
		pthread_mutex_lock(&ioMutex);
		write(serialPort, &data, 1);
		pthread_mutex_unlock(&ioMutex);
		
		//wait for car to pass over bridge
		sleep(5);
		
		//Decrease cars on bridge
		pthread_mutex_lock(&stateMutex);
		queues[0]--;
		
	}
	pthread_mutex_unlock(&stateMutex);
	print();
}

void *readSerialPort(void *arg){
	//printf("Started read serial port thread\n");
	uint8_t data = 0;
	while (1)
	{
		data = 0;
		
		//Read sent value to data
		pthread_mutex_lock(&ioMutex);
		read(serialPort, &data, 1);
		pthread_mutex_unlock(&ioMutex);
		
		if (data == 0b1010) //Both lights red
		{
			pthread_mutex_lock(&stateMutex);
			lights = RED;
			//printf("read port red: %d\n", lights);
			pthread_mutex_unlock(&stateMutex);
			print();
			
		} else if (data == 0b1001) //North green, south red
		{
			pthread_mutex_lock(&stateMutex);
			lights = NORTHGREEN;
			//printf("read port north green: %d\n", lights);
			pthread_mutex_unlock(&stateMutex);
			sem_post(&bridgeEnterSem);
			
		} else if (data == 0b0110) //South green, north red
		{
			pthread_mutex_lock(&stateMutex);
			lights = SOUTHGREEN;
			//printf("read port south green: %d\n", lights);
			pthread_mutex_unlock(&stateMutex);
			sem_post(&bridgeEnterSem);
			
		}
	}
}