/*
 * InputHandler.c
 *
 * Created: 2021-02-23 10:16:47
 *  Author: adahed-8
 */ 


#include "InputHandler.h"
#include <avr/io.h>

void sensorInterupt (InputHandler *self){
	volatile uint8_t data = UDR0;
	
	if ((data >> 0) & 1){
		// add to North queue
		ASYNC(self->controller, addQueue, 1);
	}
	
	else if ( data & northBridge ){
		// North car goes on bridge, add car on bridge
		ASYNC(self->controller, addBridge, 1);
	}
	
	else if (data & southCar){
		// add to South queue
		ASYNC(self->controller, addQueue, 2);
	}
	
	else if ( data & southBridge ){
		// South car goes on bridge, add car on bridge
		ASYNC(self->controller, addBridge, 2);
	}
}
