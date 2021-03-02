/*
 * InputHandler.h
 *
 * Created: 2021-02-23 10:17:02
 *  Author: adahed-8
 */ 


#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include "TinyTimber.h"
#include "GUI.h"
#include "PulseGenerator.h"
#include <stdbool.h>

#define leftMask (1 << 2)
#define rightMask (1 << 3)
#define upMask (1 << 6)
#define downMask (1 << 7)	
#define pressMask (1 << 4)
#define currentPG self->pG[self->gui->current]
#define waitTime 1000

typedef struct {
	Object super;
	PulseGenerator *pG[3];
	GUI *gui;
	int risingEdge;
} InputHandler;

#define initInputHandler(pGen0, pGen1, pGen2, GUI) {initObject(), {pGen0, pGen1, pGen2}, GUI, 1}
			
void initialize(InputHandler *self);

void joystickHorizontal(InputHandler *self);

void checkContinous(InputHandler *self, bool up);

void joystickVerticalPressed(InputHandler *self);

#endif /* INPUTHANDLER_H_ */