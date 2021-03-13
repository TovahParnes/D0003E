/*
 * OutputHandler.c
 *
 * Created: 2021-03-09 09:22:55
 *  Author: Adam Hedberg
 */ 
#include "OutputHandler.h"

void outputLights(OutputHandler *self, int lights){
	
	//while ( !(UCSR0A & (1<<UDRE0)) ); // Wait until empty transmit buffer

	if (lights == 0){ // North and south is Red 
		//UDR0 = 0b1010;
		UDR0 = 0x10;
	}
	if (lights == 1){ // North is Green south is Red
		//UDR0 = 0b1001;
		UDR0 = 0x9;
	}
	if (lights == 2){ // North is Red south is Green
		//UDR0 = 0b0110;	
		UDR0 = 0x6;	
	}
}