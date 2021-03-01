/*
 * Writing.c
 *
 * Created: 2021-02-22 14:47:35
 *  Author: adahed-8
 */ 

   
#include <avr/io.h>
#include "TinyTimber.h"
#include "Writing.h"

void writeToPin(PortWriter *self, int arg){
	PINE ^= (1 << arg);
}