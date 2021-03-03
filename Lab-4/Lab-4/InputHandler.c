/*
 * InputHandler.c
 *
 * Created: 2021-02-23 10:16:47
 *  Author: adahed-8
 */ 


#include "InputHandler.h"
#include <avr/io.h>

void initialize(InputHandler *self){
	SYNC(self->gui, init, NULL);
	ASYNC(self->pG[0], generatePulse, NULL);
	ASYNC(self->pG[1], generatePulse, NULL);
}

void joystickHorizontal(InputHandler *self){
	int current = self->gui->current;

	//Left
	if ((PINE & leftMask) == 0){
		if (current != 0){
			ASYNC(self->gui, changeCurrent, 0);
		}
	}
	
	//Right
	if ((PINE & rightMask) == 0){
		if (current != 1){
			ASYNC(self->gui, changeCurrent, 1);
		}
	}
}

void joystickVerticalPressed(InputHandler *self){
	#define currentPG self->pG[self->gui->current]
	//Up
	if ((PINB & upMask) == 0){
		ASYNC(currentPG, changeFreq, 1);
	}
	
	//Down
	if ((PINB & downMask) == 0){
		ASYNC(currentPG, changeFreq, -1);
	}
	
	//Pressing
	if ((PINB & pressMask) == 0){
		ASYNC(currentPG, saveLoadFreq, NULL);
	}
	
}