/*
 * PulseGenerator.c
 *
 * Created: 2021-02-22 14:37:07
 *  Author: adahed-8
 */ 


#include <avr/io.h>
#include <stdbool.h>
#include "TinyTimber.h"
#include "PulseGenerator.h"
#include "Writing.h"


void generatePulse(PulseGenerator *self){
	volatile int pinTest = self->pin;
	volatile int t = self->isHigh;
	self->isHigh = !self->isHigh;
	t = self->isHigh;
	AFTER(MSEC(500), self, generatePulse, NULL);
	
	int temp[] = {self->isHigh, self->pin};
	//ASYNC(self, writeToPin, temp); //Should not work but does
	ASYNC(self->pw, writeToPin, temp); //Should work but doesn't

	
	if (self->pin == 0){
		LCDDR13 ^= 0x1;
	} 
	if (self->pin == 6)
	{
		LCDDR18 ^= 0x1;
	}
	
}
