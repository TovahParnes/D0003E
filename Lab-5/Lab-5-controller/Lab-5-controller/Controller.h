/*
 * Cars.h
 *
 * Created: 2021-03-04 11:17:21
 *  Author: Adam Hedberg
 */ 


#ifndef CARS_H_
#define CARS_H_

#include "TinyTimber.h"
#include <avr/io.h>
#include "OutputHandler.h"
#include "GUI.h"

#define maxCarsBeforeSwap 4

//Define direction statuses
#define BRIDGE 0
#define NORTH 1
#define SOUTH 2

//Define light statuses
#define RED 0
#define NORTHGREEN 1
#define SOUTHGREEN 2

typedef struct {
	Object super; 
	int queue[3];
	int bridgeDirection;
	int lights;
	int carsPassed;
	OutputHandler *OpH;
	GUI *gui;
	}Controller;

#define initController(OpH, gui){initObject(),{0, 0, 0}, 0, 0, 0, OpH, gui}

void initialize(Controller *self);

//Queue functions
void addQueue (Controller *self, int dir);

void addBridge (Controller *self, int dir);

void decQueue (Controller *self, int dir);

void decBridge (Controller *self);

//Light functions
void lightsRed(Controller *self);

void lightGreen(Controller *self, int dir);

void lightsNorth(Controller *self);

void lightsSouth(Controller *self);


#endif /* CARS_H_ */