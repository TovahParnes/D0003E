/*
 * OutputHandler.c
 *
 * Created: 2021-03-09 09:22:55
 *  Author: Adam Hedberg
 */ 
#include "OutputHandler.h"

void outputLights(OutputHandler *self, int lights){
	
	if (lights == 0){ // North and south is Red 
		UDR0 = 0B1010;
	}
	if (lights == 1){ // North is Green south is Red
		UDR0 = 0B1001;
	}
	if (lights == 2){ // North is Red south is Green
		UDR0 = 0B0110;	
	}
}