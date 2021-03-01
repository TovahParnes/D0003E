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

typedef struct {
	Object super;
	PulseGenerator *pG[3];
	GUI *gui;
	int risingEdge;
} InputHandler;

#define initInputHandler(pGen0, pGen1, pGen2, GUI) {initObject(), {pGen0, pGen1, pGen2}, GUI, 1}
			
void initialize(InputHandler *self);

#endif /* INPUTHANDLER_H_ */