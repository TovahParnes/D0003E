/*
 * Cars.h
 *
 * Created: 2021-03-04 11:17:21
 *  Author: Adam Hedberg
 */ 


#ifndef CARS_H_
#define CARS_H_

#include "TinyTimber.h"
#include "InputHandler.h"


#define maxCarsBeforeSwap 10

typedef struct {
	Object super; 
	int bridgeDirection;
	int northQueue;
	int southQueue; 
	int bridgeQueue;
	int lights;
	int carsPassed;
	GUI *gui;
	}Controller;

#define initQueueAndDirection(gui){initObject(), 0, 0, 0, 0, 0, 0, gui}
 

void addQueue (Controller *self, int dir);

void addBridge (Controller *self, int dir);

void decQueue (Controller *self, int dir);

void decBridge (Controller *self, int dir);

int longestQueue (Controller *Self);

void lightOnOff(Controller *self);

void lightsRed(Controller *self);

void lightGreen(Controller *self, int dir);

void lightsAddBridge(Controller *self);

void lightsBridgeEmpty(Controller *self);


#endif /* CARS_H_ */