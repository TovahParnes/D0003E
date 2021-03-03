/*
 * PulseGenerator.h
 *
 * Created: 2021-02-22 14:37:21
 *  Author: adahed-8
 */ 


#ifndef PULSEGENERATOR_H_
#define PULSEGENERATOR_H_

#include "TinyTimber.h"
#include "Writing.h"
#include "GUI.h"

#define upMask (1 << 6)
#define downMask (1 << 7)
#define waitTime 150

#define initPulseGenerator(pw, gui, pin, savedFreq) {initObject(), pw, gui, pin, 0, savedFreq, 0}

typedef struct {
	Object super;
	PortWriter *pw;
	GUI *gui;
	int pin, freq, savedFreq, isHigh;
} PulseGenerator;
				
void generatePulse(PulseGenerator *self);

void checkContinous(PulseGenerator *self, int value);

void changeFreq(PulseGenerator *self, int value);

void saveLoadFreq(PulseGenerator *self);

#endif /* PULSEGENERATOR_H_ */