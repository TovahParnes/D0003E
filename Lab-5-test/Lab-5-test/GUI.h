/*
 * GUI.h
 *
 * Created: 2021-03-12 10:45:10
 *  Author: adahed-8
 */ 


#ifndef GUI_H_
#define GUI_H_

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>

#define CLEAR printf("\x1B[2J");

pthread_mutex_t tuiMutex;
sem_t tuiSem;
uint8_t runTUI, readyToUpdateTUI;

void initGUI(void);
void *draw(void *arg);

#endif /* GUI_H_ */