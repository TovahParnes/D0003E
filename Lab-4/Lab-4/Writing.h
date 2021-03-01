/*
 * Writing.h
 *
 * Created: 2021-02-22 14:47:47
 *  Author: adahed-8
 */ 


#ifndef WRITING_H_
#define WRITING_H_

#include "TinyTimber.h"

typedef struct {
	Object super;
} PortWriter;

#define initPortWriter() \
{ initObject()}
	
void turnOffPin(PortWriter *self, int pin);

void invertPin(PortWriter *self, int pin);

#endif /* WRITING_H_ */