/*
 * Cars.h
 *
 * Created: 2021-03-04 11:17:21
 *  Author: Adam Hedberg
 */ 


#ifndef CARS_H_
#define CARS_H_

typedef struct {
	Object super; 
	int bridgeDirection;
	int northQueue;
	int southQueue; 
	int bridgeQueue;
	}QueueAndDirection;

#define initQueueAndDirection(){initObject(), 0,0,0,0}


void addQueue (QueueAndDirection *self, int dir);

void addBridge (QueueAndDirection *self, int dir);

void decQueue (QueueAndDirection *self, int dir);

void decBridge (QueueAndDirection *self, int dir);

#endif /* CARS_H_ */