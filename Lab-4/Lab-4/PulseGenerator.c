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
		ASYNC(self->pw, turnOffPin, self->pin);
		AFTER(MSEC(500), self, generatePulse, NULL);
	} else {
		ASYNC(self->pw, invertPin, self->pin);
		AFTER(USEC(500000/self->savedFreq), self, generatePulse, NULL);
	}
}

void checkContinous(PulseGenerator *self, int value){
	if (value == 1){
		if ((PINB & upMask) == 0){
			ASYNC(self, changeFreq, value);
			//AFTER(MSEC(waitTime), self, checkContinous, true);
		}
	} else {
		if ((PINB & downMask) == 0){
			ASYNC(self, changeFreq, value);
			//AFTER(MSEC(waitTime), self, checkContinous, false);
		}
	}
}

void changeFreq(PulseGenerator *self, int value){
	if ((self->freq + value) >= 0 && (self->freq + value) <= 99){
		self->freq = self->freq + value;
		ASYNC(self->gui, updateDisplayedFreq, self->freq);
		AFTER(MSEC(waitTime), self, checkContinous, value);
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
