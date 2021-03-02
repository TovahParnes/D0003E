/*
 * PulseGenerator.c
 *
 * Created: 2021-02-22 14:37:07
 *  Author: adahed-8
 */ 

#include "PulseGenerator.h"
#include <avr/io.h>

void generatePulse(PulseGenerator *self){
	if (self->savedFreq == 0){
		SYNC(self->pw, turnOffPin, self->pin);
		AFTER(MSEC(500), self, generatePulse, NULL);
	} else {
		SYNC(self->pw, invertPin, self->pin);
		AFTER(USEC(500000/self->savedFreq), self, generatePulse, NULL);
	}
}

void changeFreq(PulseGenerator *self, int value){
	if ((self->freq + value) >= 0 && (self->freq + value) <= 99){
		self->freq = self->freq + value;
		ASYNC(self->gui, updateDisplayedFreq, self->freq);
	}
}

void saveLoadFreq(PulseGenerator *self){
	if (self->freq == 0){
		self->freq = self->savedFreq;
	} else {
		self->savedFreq = self->freq;
		self->freq = 0;
	}
	
	ASYNC(self->gui, updateDisplayedFreq, self->freq);
}
