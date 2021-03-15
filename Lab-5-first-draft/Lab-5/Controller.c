/*
 * Carsc.c
 *
 * Created: 2021-03-04 11:17:02
 *  Author: Adam Hedberg
 */ 
#include "Controller.h"

void addQueue (Controller *self, int dir){
	if (dir == NORTH){
		self->queue[NORTH]++;
		ASYNC(self->gui, displayNorthQueue, self->queue[NORTH]);
	}
	else if(dir == SOUTH){
		self->queue[SOUTH]++;
		ASYNC(self->gui, displaySouthQueue, self->queue[SOUTH]);
	}
}

void addBridge (Controller *self, int dir){
	decQueue(self,dir);
	self->bridgeDirection = dir; 
	self->carsPassed++;
	self->queue[BRIDGE]++;
	ASYNC(self->gui, displayBridgeQueue, self->queue[BRIDGE]);
	AFTER(SEC(5),self, decBridge, NULL);

}

void decQueue (Controller *self, int dir){
	if (dir == NORTH){
		self->queue[NORTH]--;
		ASYNC(self->gui, displayNorthQueue, self->queue[NORTH]);
	}
	else if(dir == SOUTH){
		self->queue[SOUTH]--;
		ASYNC(self->gui, displaySouthQueue, self->queue[SOUTH]);
	}
}

void decBridge (Controller *self){
	self->queue[BRIDGE]--;
	if (self->queue[BRIDGE] == 0){
	}
	ASYNC(self->gui, displayBridgeQueue, self->queue[BRIDGE]);
}


int longestQueue (Controller *self){
	if (self->queue[NORTH] >= self->queue[SOUTH]){
		return NORTH;
	}
	else {
		return SOUTH;
	}
}

int shortestQueue (Controller *self){
	if (self->queue[NORTH] >= self->queue[SOUTH]){
		return SOUTH;
	}
	else {
		return NORTH;
	}
}



void lightsRed(Controller *self){
	self->carsPassed = 0;
	self->lights = RED;
	ASYNC(self->OpH, outputLights, self->lights );
}

void lightGreen(Controller *self, int dir){
	self->lights = dir;
	ASYNC(self->OpH, outputLights, self->lights );
}


void lightsBridge(Controller *self){
	int longest = longestQueue(self);
	
	switch (longest)
	{
	case NORTH:
		lightsNorth(self);
		break;
		
	case SOUTH:
		lightsSouth(self);
		break;
	}
	
	/*if (self->queue[BRIDGE] == 0){
		lightGreen(self, longest);
		AFTER(SEC(1), self, lightsBridge, NULL);
	}
	else {
		if (longest == self->bridgeDirection){
			if (self->carsPassed >= maxCarsBeforeSwap){
				if (shortest != 0){
					self->carsPassed == 0;
					lightsRed(self);
					AFTER(SEC(5), self, lightGreen, shortest);
					AFTER(SEC(6), self, lightsBridge, NULL);
				}
				else {
					lightGreen(self, longest);
					AFTER(SEC(1), self, lightsBridge, NULL);
				}	
			} 
			else {
				lightGreen(self, longest);
				AFTER(SEC(1), self, lightsBridge, NULL);
			}
		}
		else {
			self->carsPassed == 0;
			lightsRed(self);
			AFTER(SEC(5), self, lightGreen, shortest);
			AFTER(SEC(6), self, lightsBridge, NULL);
		}
	}*/
}

void lightsNorth(Controller *self){
	if (self->queue[NORTH] > 0 && (self->carsPassed <= maxCarsBeforeSwap || self->queue[SOUTH] == 0)){
		lightGreen(self, NORTH);
		AFTER(SEC(1), self, lightsNorth, NULL);
	} else if (self->queue[BRIDGE] != 0 && self->queue[SOUTH] != 0 && self->bridgeDirection == NORTH){
		lightsRed(self);
		AFTER(SEC(5), self, lightsSouth, NULL);
	} else {
		lightsRed(self);
		AFTER(SEC(1), self, lightsSouth, NULL);
	}
}

void lightsSouth(Controller *self){
	if (self->queue[SOUTH] > 0 && (self->carsPassed <= maxCarsBeforeSwap || self->queue[NORTH] == 0)){
		lightGreen(self, SOUTH);
		AFTER(SEC(1), self, lightsSouth, NULL);
	}
	else if (self->queue[BRIDGE] != 0 && self->queue[NORTH] != 0 && self->bridgeDirection == SOUTH){
		lightsRed(self);
		AFTER(SEC(5), self, lightsNorth, NULL);
	} else {
		lightsRed(self);
		AFTER(SEC(1), self, lightsNorth, NULL);
	}
}

void initialize(Controller *self){
	ASYNC(self->gui, init, NULL);
	ASYNC(self->gui, displayNorthQueue, self->queue[NORTH]);
	ASYNC(self->gui, displaySouthQueue, self->queue[SOUTH]);
	ASYNC(self->gui, displayBridgeQueue, self->queue[BRIDGE]);
	ASYNC(self, lightsNorth, NULL);
	}