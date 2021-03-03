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


typedef struct {
	Object super;
	PulseGenerator *pG[2];
	GUI *gui;
} InputHandler;

#define initInputHandler(pGen1, pGen2, gui) {initObject(), {pGen1, pGen2}, gui}
			
void initialize(InputHandler *self);

void joystickHorizontal(InputHandler *self);

void joystickVerticalPressed(InputHandler *self);

#endif /* INPUTHANDLER_H_ */