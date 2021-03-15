/*
 * LCd.h
 *
 * Created: 2021-02-15 10:47:42
 *  Author: tovah
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "TinyTimber.h"

typedef struct {
	Object super;
} GUI;

#define initGUI() { initObject()}
			
void writeChar(char ch, int pos);

void init(GUI *self);

void initLCD (void); 

void initUSART (void);

void displayNorthQueue (GUI *self,int num);

void displaySouthQueue (GUI *self,int num);

void displayBridgeQueue (GUI *self,int num);

#endif /* LCD_H_ */