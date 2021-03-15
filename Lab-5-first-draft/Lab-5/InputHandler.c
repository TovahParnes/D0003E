/*
 * InputHandler.c
 *
 * Created: 2021-02-23 10:16:47
 *  Author: adahed-8
 */ 


#include "InputHandler.h"
#include <avr/io.h>

void sensorInterupt (InputHandler *self, uint8_t arg){
	volatile uint8_t data = UDR0;
	
	if ((data >> 0) & 1){
		// add to Nqueue
		ASYNC(self->controller, addQueue, 1);
	}
	
	else if ( data & northBridge ){
		// North car goes on bridge add total car on bridge
		ASYNC(self->controller, addBridge, 1);
	}
	
	else if (data & southCar){
		// add to Squeue
		ASYNC(self->controller, addQueue, 2);
	}
	
	else if ( data & southBridge ){
		// South car goes on bridge add total car on bridge
		ASYNC(self->controller, addBridge, 2);
	}
}
