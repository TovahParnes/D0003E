/*
 * state.h
 *
 * Created: 2021-03-12 10:47:42
 *  Author: adahed-8
 */ 


#ifndef STATE_H_
#define STATE_H_

#include <semaphore.h>
#include <stdint.h>
#include <pthread.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

//Define direction statuses
#define BRIDGE 0
#define NORTH 1
#define SOUTH 2

//Define bridge statuses
#define RED 0
#define NORTHGREEN 1
#define SOUTHGREEN 2

sem_t arrivalSem;
sem_t bridgeEnterSem;

pthread_mutex_t stateMutex; //Mutex for state variables
pthread_mutex_t ioMutex; //Mutex for writing and reading

uint64_t arrivalDir;
uint64_t queues[3];
uint8_t lights;
int serialPort;
static struct termios serialSettings;

void initState(void);
void *arrivalWait(void *arg);
void arrival(uint64_t dir);
void *bridgeEnter(void *arg);
void *carOnBridge(void *arg);
void *readSerialPort(void *arg);

#endif /* STATE_H_ */