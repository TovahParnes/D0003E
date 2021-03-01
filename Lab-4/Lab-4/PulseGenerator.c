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
	
	if (self->pin == 4){
		LCDDR13 ^= 0x1;
	} 
	if (self->pin == 6)
	{
		LCDDR18 ^= 0x1;
	}

	if (self->savedFreq == 0){
		SYNC(self->pw, turnOffPin, self->pin);
		AFTER(MSEC(500), self, generatePulse, NULL);
	} else {
		SYNC(self->pw, invertPin, self->pin);
		AFTER(USEC(500000/self->savedFreq), self, generatePulse, NULL);
	}
	
	
}
