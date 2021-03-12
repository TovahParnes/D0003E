/*
 * state.h
 *
 * Created: 2021-03-12 10:47:42
 *  Author: adahed-8
 */ 


#ifndef STATE_H_
#define STATE_H_

#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t ioMutex;
sem_t stateLoopSem;
pthread_mutex_t stateMutex;
sem_t arrivalSem;
uint64_t arrivalDirection;

uint64_t carsNorth;
uint64_t carsSouth;

void initState(void);
void *arrivalWait(void *arg);

#endif /* STATE_H_ */