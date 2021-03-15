/*
 * OutputHandler.c
 *
 * Created: 2021-03-09 09:22:55
 *  Author: Adam Hedberg
 */ 
#include "OutputHandler.h"

void outputLights(OutputHandler *self, int lights){
	if (lights == 0){ // North and south is Red 
		UDR0 = 0xA; // 0xA = 0b1010
	}
	 else if (lights == 1){ // North is Green south is Red
		UDR0 = 0x9; //Ox9 = 0b1001
	}
	else if (lights == 2){ // North is Red south is Green
		UDR0 = 0x6;	//0x6 = 0b0110
	}
}