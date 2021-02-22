/*
 * PulseGenerator.h
 *
 * Created: 2021-02-22 14:37:21
 *  Author: adahed-8
 */ 


#ifndef PULSEGENERATOR_H_
#define PULSEGENERATOR_H_

#include "TinyTimber.h"

typedef struct {
	Object super;
	PortWriter *pw;
	int pin, freq, savedFreq, isHigh;
} PulseGenerator;

#define initPulseGenerator(PortWriter, pin) \
{initObject(), PortWriter, pin, 0, 0}

void generatePulse(PulseGenerator *self);

#endif /* PULSEGENERATOR_H_ */