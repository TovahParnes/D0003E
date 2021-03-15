/*
 * Carsc.c
 *
 * Created: 2021-03-04 11:17:02
 *  Author: Adam Hedberg
 */ 
#include "Controller.h"

void addQueue (Controller *self, int dir){
	if (dir == NORTH){ 
		//Add car to north queue
		self->queue[NORTH]++;
		ASYNC(self->gui, displayNorthQueue, self->queue[NORTH]);
	}
	else if(dir == SOUTH){
		//Add car to south queue
		self->queue[SOUTH]++;
		ASYNC(self->gui, displaySouthQueue, self->queue[SOUTH]);
	}
}

void addBridge (Controller *self, int dir){
	decQueue(self, dir);		//Decrease car from current queue
	self->bridgeDirection = dir; 
	self->carsPassed++;
	self->queue[BRIDGE]++;
	ASYNC(self->gui, displayBridgeQueue, self->queue[BRIDGE]);
	AFTER(SEC(5),self, decBridge, NULL);		//Decrease cars on bridge after 5 sec

}

void decQueue (Controller *self, int dir){
	if (dir == NORTH){
		//Decrease cars on north queue
		self->queue[NORTH]--;
		ASYNC(self->gui, displayNorthQueue, self->queue[NORTH]);
	}
	else if(dir == SOUTH){
		//Decrease cars on south queue
		self->queue[SOUTH]--;
		ASYNC(self->gui, displaySouthQueue, self->queue[SOUTH]);
	}
}

void decBridge (Controller *self){
	// Decrease cars on bridge
	self->queue[BRIDGE]--;
	ASYNC(self->gui, displayBridgeQueue, self->queue[BRIDGE]);
}

void lightsRed(Controller *self){
	//Set both lights to red
	self->carsPassed = 0;		//Reset the amount of cars that has passed the bridge
	self->lights = RED;
	ASYNC(self->OpH, outputLights, self->lights );
}

void lightGreen(Controller *self, int dir){
	//Set light in direction dir to green, the other to red
	self->lights = dir;
	ASYNC(self->OpH, outputLights, self->lights );
}

void lightsNorth(Controller *self){
	// North cars can pass if:
	// There are cars in the north queue AND
	// The set amount of cars has not passed OR there are no cars in the south queue
	if (self->queue[NORTH] > 0 && (self->carsPassed <= maxCarsBeforeSwap || self->queue[SOUTH] == 0)){
		lightGreen(self, NORTH);
		AFTER(SEC(1), self, lightsNorth, NULL);
		
	// Change to the south queue after 5 sec if:
	// There are cars on the bridge AND
	// There are cars in the south queue AND
	// The bridge direction is north
	} else if (self->queue[BRIDGE] != 0 && self->queue[SOUTH] != 0 && self->bridgeDirection == NORTH){
		lightsRed(self);
		AFTER(SEC(5), self, lightsSouth, NULL);
	
	// If both queues are empty, set lights red
	// Will become a loop between lightsSouth and lightsNorth
	} else {
		lightsRed(self);
		AFTER(SEC(1), self, lightsSouth, NULL);
	}
}

void lightsSouth(Controller *self){
	// South cars can pass if:
	// There are cars in the south queue AND
	// The set amount of cars has not passed OR there are no cars in the north queue
	if (self->queue[SOUTH] > 0 && (self->carsPassed <= maxCarsBeforeSwap || self->queue[NORTH] == 0)){
		lightGreen(self, SOUTH);
		AFTER(SEC(1), self, lightsSouth, NULL);
	
	// Change to the north queue after 5 sec if:
	// There are cars on the bridge AND
	// There are cars in the north queue AND
	// The bridge direction is south
	} else if (self->queue[BRIDGE] != 0 && self->queue[NORTH] != 0 && self->bridgeDirection == SOUTH){
		lightsRed(self);
		AFTER(SEC(5), self, lightsNorth, NULL);
		
	// If both queues are empty, set lights red
	// Will become a loop between lightsSouth and lightsNorth
	} else {
		lightsRed(self);
		AFTER(SEC(1), self, lightsNorth, NULL);
	}
}

void initialize(Controller *self){
	ASYNC(self->gui, init, NULL); 
	
	//Display current queues
	ASYNC(self->gui, displayNorthQueue, self->queue[NORTH]); 
	ASYNC(self->gui, displaySouthQueue, self->queue[SOUTH]);
	ASYNC(self->gui, displayBridgeQueue, self->queue[BRIDGE]);
	
	//Initiate light
	ASYNC(self, lightsNorth, NULL);
	}