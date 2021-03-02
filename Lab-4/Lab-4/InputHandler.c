/*
 * InputHandler.c
 *
 * Created: 2021-02-23 10:16:47
 *  Author: adahed-8
 */ 


#include "InputHandler.h"
#include <avr/io.h>

void initialize(InputHandler *self){
	SYNC(self->gui, LCD_INIT, NULL);
	SYNC(self->gui, Button_INIT, NULL);
	ASYNC(self->pG[1], generatePulse, NULL);
	ASYNC(self->pG[2], generatePulse, NULL);
}

void joystickHorizontal(InputHandler *self){
	int current = self->gui->current;
	
	//Left
	if ((PINE & leftMask) == 0){
		if (current != 1){
			ASYNC(self->gui, changeCurrent, 1);
		}
	}
	
	//Right
	if ((PINE & rightMask) == 0){
		if (current != 2){
			ASYNC(self->gui, changeCurrent, 2);
		}
	}
}

void checkContinous(InputHandler *self, bool up){
	if (up){
		if ((PINB & upMask) == 0){
			ASYNC(currentPG, changeFreq, 1);
			AFTER(MSEC(waitTime), self, checkContinous, true);
		}
	} else {
		if ((PINB & downMask) == 0){
			ASYNC(currentPG, changeFreq, -1);
			AFTER(MSEC(waitTime), self, checkContinous, false);
		}
	}
}

void joystickVerticalPressed(InputHandler *self){
	//Up
	if ((PINB & upMask) == 0){
		ASYNC(currentPG, changeFreq, 1);
		AFTER(MSEC(waitTime), self, checkContinous, true);
	}
	
	//Down
	if ((PINB & downMask) == 0){
		ASYNC(currentPG, changeFreq, -1);
		AFTER(MSEC(waitTime), self, checkContinous, false);
	}
	
	//Pressing
	if ((PINB & pressMask) == 0){
		ASYNC(currentPG, saveLoadFreq, NULL);
	}
	
}