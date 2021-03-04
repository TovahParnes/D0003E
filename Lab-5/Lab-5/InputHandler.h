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

#define northCar (1 << 0)
#define northBridge (1 << 1)
#define southCar (1 << 2)
#define southBridge (1 << 3)


typedef struct {
	Object super;
	QueueAndDirection QaD;
	GUI *gui;
} InputHandler;

#define initInputHandler(QaD,gui) {initObject(),QaD, gui}

	
void initialize(InputHandler *self);

#endif /* INPUTHANDLER_H_ */