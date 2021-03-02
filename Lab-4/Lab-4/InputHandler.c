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
	int current = self->gui->current;
	#define leftMask (1 << 2)
	#define rightMask (1 << 3)
	
	
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

void joystickVerticalPressed(InputHandler *self){
	#define upMask (1 << 6)
	#define downMask (1 << 7)
	#define pressMask (1 << 4)
	#define currentPG self->pG[self->gui->current]
	#define period 450
	
	//Up
	if ((PINB & upMask) == 0){
		AFTER(MSEC(period), currentPG, changeFreq, 1);
	}
	
	//Down
	if ((PINB & downMask) == 0){
		AFTER(MSEC(period), currentPG, changeFreq, -1);
	}
	
	//Pressing
	if ((PINB & pressMask) == 0){
		ASYNC(currentPG, saveLoadFreq, NULL);
	}
	
}