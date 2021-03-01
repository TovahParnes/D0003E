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
	ASYNC(self->pG[1], generatePulse, NULL);
	ASYNC(self->pG[2], generatePulse, NULL);
}