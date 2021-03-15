/*
 * GUI.h
 *
 * Created: 2021-03-12 10:45:10
 *  Author: adahed-8
 */ 


#ifndef GUI_H_
#define GUI_H_

#include <semaphore.h>
#include <stdint.h>
#include <pthread.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define CLEAR printf("\x1B[2J");

static struct termios prgmTerminalSettings;

void initGUI(void);
void print(void);
void terminalSettings(void);

#endif /* GUI_H_ */