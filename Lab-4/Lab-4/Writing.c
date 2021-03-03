/*
 * Writing.c
 *
 * Created: 2021-02-22 14:47:35
 *  Author: adahed-8
 */ 


#include "Writing.h"
#include <avr/io.h>

void turnOffPin(PortWriter *self, int pin){
	PINE &= ~(1 << pin);
	blinkDisplay(pin);
}

void invertPin(PortWriter *self, int pin){
	PINE ^= (1 << pin); 
	blinkDisplay(pin);
}

void blinkDisplay(int pin){
	int temp = PINE;
	int value = (temp >> pin) & 1;
	
	if (pin == 4){
		LCDDR13 = value;
	}
	if (pin == 6)
	{
		LCDDR18 = value;
	}
}