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

#define initPulseGenerator(pw, gui, pin) {initObject(), pw, gui, pin, 0, 0, 0}

typedef struct {
	Object super;
	PortWriter *pw;
	GUI *gui;
	int pin, freq, savedFreq, isHigh;
} PulseGenerator;
				
void generatePulse(PulseGenerator *self);

void saveFrec(PulseGenerator *self);

void loadFrec(PulseGenerator *self);

void changeFrec(PulseGenerator *self);

#endif /* PULSEGENERATOR_H_ */