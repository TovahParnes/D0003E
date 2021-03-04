/*
 * Carsc.c
 *
 * Created: 2021-03-04 11:17:02
 *  Author: Adam Hedberg
 */ 

void addQueue (QueueAndDirection *self, int dir){
	if (dir == 1){
		self->northQueue++;
	}
	else if(dir == 2){
		self->southQueue++;
	}
	
}

void addBridge (QueueAndDirection *self, int dir){
	decQueue(self,dir);
	self->bridgeDirection = dir; 
	self->bridgeQueue++;
	AFTER(SEC(5),self, decBridge, dir);
}

void decQueue (QueueAndDirection *self, int dir){
	if (dir == 1){
		self->northQueue--;
	}
	else if(dir == 2){
		self->southQueue--;
	}
	
}

void decBridge (QueueAndDirection *self, int dir){
	self->bridgeQueue--;
	if (self->bridgeQueue == 0){
		self->bridgeDirection = 0;
	}
}
