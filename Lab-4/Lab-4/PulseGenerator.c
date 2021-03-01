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
	if (self->savedFreq == 0){
		SYNC(self->pw, turnOffPin, self->pin);
		AFTER(MSEC(500), self, generatePulse, NULL);
	} else {
		SYNC(self->pw, invertPin, self->pin);
		AFTER(USEC(500000/self->savedFreq), self, generatePulse, NULL);
	}
}
