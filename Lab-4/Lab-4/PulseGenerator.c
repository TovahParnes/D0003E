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
	volatile int t = self->isHigh;
	self->isHigh = !self->isHigh;
	t = self->isHigh;
	//AFTER(MSEC(500), self, generatePulse, NULL);
	ASYNC(self, generatePulse, NULL);
	
	//int temp[] = {self->isHigh, self->pin};
	//ASYNC(self->pw, writeToPin, temp);
	
	volatile int p = self->pin;
	
	if (self->pin == 4){
		LCDDR13 ^= 0x1;
	} 
	if (self->pin == 0)
	{
		LCDDR18 ^= 0x1;
	}
	
	
	/*
	if(self->frequency == 0){
		self->isHigh = 0;
		
		AFTER(MSEC(500), self, generatePulse, NULL);
	}
	else{
		self->isHigh = !self->isHigh;
		
		AFTER(USEC(500000/self->frequency), self, generatePulse, NULL);
	}
	
	int temp[] = {self->isHigh, self->pin};
	ASYNC(self->pWriter, writeToPin, temp);
	*/
}
