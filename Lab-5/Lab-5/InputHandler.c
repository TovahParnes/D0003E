/*
 * InputHandler.c
 *
 * Created: 2021-02-23 10:16:47
 *  Author: adahed-8
 */ 


#include "InputHandler.h"
#include <avr/io.h>

void sensorInterupt (InputHandler *self){
	
	if ( UDR0 & northCar ){
		// add to Nqueue
		ASYNC(self->controller, addQueue, 1);
		
	}
	
	if ( UDR0 & northBridge ){
		// North car goes on bridge add total car on bridge
		ASYNC(self->controller, addBridge, 1);
	}
	
	if ( UDR0 & southCar ){
		// add to Squeue
		ASYNC(self->controller, addQueue, 2);
	}
	
	if ( UDR0 & southBridge ){
		// South car goes on bridge add total car on bridge
		ASYNC(self->controller, addBridge, 2);
	}
}
