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

typedef struct {
	Object super;
	PortWriter *pw;
	int pin, frequency, savedFreq;
	bool isHigh;
} PulseGenerator;


void generatePulse(PulseGenerator *self){
	self->isHigh = !self->isHigh;
	AFTER(MSEC(500), self, generatePulse, NULL);
	
	int temp[] = {self->isHigh, self->pin};
	ASYNC(self->pw, writeToPin, temp);
	
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