/*
 * OutputHandler.h
 *
 * Created: 2021-03-09 09:23:17
 *  Author: Adam Hedberg
 */ 


#ifndef OUTPUTHANDLER_H_
#define OUTPUTHANDLER_H_

#include "TinyTimber.h"
#include <avr/io.h>

typedef struct {
	Object super;
	
	}OutputHandler;

#define initOutputHandler(){initObject()}

void outputLights(OutputHandler *self, int lights);

#endif /* OUTPUTHANDLER_H_ */