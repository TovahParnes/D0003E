/*
 * Writing.c
 *
 * Created: 2021-02-22 14:47:35
 *  Author: adahed-8
 */ 

   
#include <avr/io.h>
#include "TinyTimber.h"
#include "Writing.h"

typedef struct {
	Object super;
} PortWriter;


void writeToPin(PortWriter *self, int args[]){
	PINE = (args[0] << args[1]);
}