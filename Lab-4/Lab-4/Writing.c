/*
 * Writing.c
 *
 * Created: 2021-02-22 14:47:35
 *  Author: adahed-8
 */ 


#include "Writing.h"
#include <avr/io.h>

void turnOffPin(PortWriter *self, int pin){
	PORTE &= ~(1 << pin);
	blinkDisplay(0, pin);
}

void invertPin(PortWriter *self, int pin){
	PORTE ^= (1 << pin); 
	int temp = (PORTE >> pin) & 1;
	blinkDisplay(temp, pin);
}

void blinkDisplay(int value, int pin){
	if (pin == 4){
		LCDDR13 = value;
	}
	if (pin == 6)
	{
		LCDDR18 = value;
	}
}