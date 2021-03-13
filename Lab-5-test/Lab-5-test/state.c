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


int serialFD;
static struct termios serialSettings;
carsNorth = 0;
carsSouth = 0;

void initState(void) {
	printf("init state\n");
	/*
	serialFD = open("/dev/ttyS0", O_RDWR);

	if (serialFD == -1) printf("\x1B[20;1HFailed to open /dev/ttyS0");
	else printf("\x1B[20;1HserialFD = %d", serialFD);

	tcgetattr(serialFD, &serialSettings);

	fcntl(serialFD, F_SETFL, O_NONBLOCK);

	cfsetospeed(&serialSettings, B9600);
	cfsetispeed(&serialSettings, B9600);

	if (pthread_mutex_init(&ioMutex, NULL) != 0) printf("\x1B[21;1HFailed to create ioMutex");
	if (pthread_mutex_init(&stateMutex, NULL) != 0) printf("\x1B[21;1HFailed to create stateMutex");

	sem_init(&stateLoopSem, 0, 0);
	sem_init(&arrivalSem, 0, 0);

	bridgeEmpty = 1;
	pendingEnter = 0;

	// TODO debug
	lightStatus = BOTHRED;
	arrivalBuffers[SOUTHBOUND] = 0;
	arrivalBuffers[NORTHBOUND] = 0;
	//uint8_t a = 0;
	for (int i = 0; i < MAXCARSONBRIDGE; i++) {
		bridgeBuffer[i] = NOCAR;
		//bridgeBuffer[i] = a ? CARSOUTH : CARNORTH;
		//a = a ? 0 : 1;
	}
	//debug

	//updateState();

	//return NULL;
	*/
}

void *arrivalWait(void *arg) {
	uint64_t directionArg;
	while (1) {
		sem_wait(&arrivalSem);
		printf("\x1B[38;0Hstatetry 8");
		pthread_mutex_lock(&stateMutex);
		printf("\x1B[38;0Hstatemut 8");
		directionArg = arrivalDirection;
		pthread_mutex_unlock(&stateMutex);
		arrival(directionArg);
	}

	return NULL;
}

void arrival(uint64_t dir) {
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
}