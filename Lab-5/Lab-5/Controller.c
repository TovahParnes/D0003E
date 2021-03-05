/*
 * Carsc.c
 *
 * Created: 2021-03-04 11:17:02
 *  Author: Adam Hedberg
 */ 
#include "Controller.h"

void addQueue (Controller *self, int dir){
	if (dir == 1){
		self->northQueue++;
		int temp[2] = {self->northQueue,0};
		ASYNC(self->gui,uppdateQueue,temp);
	}
	else if(dir == 2){
		self->southQueue++;
		int temp[2] = {self->southQueue,0};
		ASYNC(self->gui,uppdateQueue,temp);
	}
}

void addBridge (Controller *self, int dir){
	decQueue(self,dir);
	self->bridgeDirection = dir; 
	self->bridgeQueue++;
	int temp[2] = {self->bridgeQueue,0}; 
	ASYNC(self,lightsAddBridge, dir);
	ASYNC(self->gui,uppdateQueue,temp);
	AFTER(SEC(5),self, decBridge, dir);

}

void decQueue (Controller *self, int dir){
	if (dir == 1){
		self->northQueue--;
		int temp[2] = {self->northQueue,0}; 
		ASYNC(self->gui,uppdateQueue,temp);
	}
	else if(dir == 2){
		self->southQueue--;
		int temp[2] = {self->southQueue,0}; 
		ASYNC(self->gui,uppdateQueue,temp);
	}
	
}

void decBridge (Controller *self, int dir){
	self->bridgeQueue--;
	if (self->bridgeQueue == 0){
		ASYNC(self,lightsBridgeEmpty,NULL);
	}
	int temp[2] = {self->bridgeQueue,0}; 
	ASYNC(self->gui,uppdateQueue,temp);
}


int longestQueue (Controller *self){
	if (self->northQueue >= self->southQueue){
		return 1;
	}
	else {
		return 2;
	}
}



void lightOnOff(Controller *self){
/*	
	if (self->QaD->bridgeQueue == 0){
		if (self->QaD->northQueue >= self->QaD->southQueue){
			self->nortLight = 1;
			self->soutLight = 0; // temp 
			self->lastDir = 1;
		}
		else {
			self->soutLight = 1;
			self->nortLight = 0; // temp 
			self->lastDir = 2;
		}
	}
	*/
}

void lightsRed(Controller *self){
	self->lights = 0;

}

void lightGreen(Controller *self, int dir){
	self->carsPassed =0;
	self->lights = dir;
}


void lightsAddBridge(Controller *self){
	self->carsPassed++;
	int longest = longestQueue(self);
	if (longest == self->bridgeDirection){
		if (self->carsPassed >= maxCarsBeforeSwap){
			lightsRed(self);
		}
	}
	else {
		lightsRed(self);
	}

	
}

void lightsBridgeEmpty(Controller *self){
	if (self->bridgeDirection == 1){
		if (self->southQueue != 0){
			lightGreen(self,2);
		}
		else {
			lightGreen(self, 1);
		}
	}
	else {
		if (self->northQueue != 0){
			lightGreen(self,1);
		}	
		else {
			lightGreen(self, 2);
		}
	}
}