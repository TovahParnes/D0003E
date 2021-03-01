/*
 * Writing.c
 *
 * Created: 2021-02-22 14:47:35
 *  Author: adahed-8
 */ 

   
#include <avr/io.h>
#include "TinyTimber.h"
#include "Writing.h"


void turnOffPin(PortWriter *self, int pin){
	writeToPin(0, pin);
}

void invertPin(PortWriter *self, int pin){
	int value = (PINE & (1 << pin) >> pin);
	writeToPin(value, pin);
}

void writeToPin(int value, int pin){
	int mask = (1 << pin);
	PINE = (PINE & ~mask) | ((value << pin) & mask);
	
	
	if (pin == 4){
		LCDDR13 ^= 0x1;
	}
	if (pin == 6)
	{
		LCDDR18 ^= 0x1;
	}
}