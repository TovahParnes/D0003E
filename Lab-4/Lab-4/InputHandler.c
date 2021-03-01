/*
 * InputHandler.c
 *
 * Created: 2021-02-23 10:16:47
 *  Author: adahed-8
 */ 


#include <avr/io.h>
#include <stdbool.h>
#include "TinyTimber.h"
#include "PulseGenerator.h"
#include "InputHandler.h"


void initialize(InputHandler *self){
	SYNC(self->gui, LCD_INIT, NULL);
	SYNC(self->gui, Button_INIT, NULL);
	ASYNC(self->pG[1], generatePulse, NULL);
	ASYNC(self->pG[2], generatePulse, NULL);
}

void joystickHorizontal(InputHandler *self){
	#define leftMask (1 << 2)
	#define rightMask (1 << 3)
	
	if ((PINE & leftMask) == 0){
		ASYNC(self->gui, changeCurrent, 1);
	}
	
	if ((PINE & rightMask) == 0){
		ASYNC(self->gui, changeCurrent, 2);
	}
}

void joystickVerticalPressed(InputHandler *self){
}