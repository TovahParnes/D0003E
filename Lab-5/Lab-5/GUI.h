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
	int current;
} GUI;

#define initGUI() \
		{ initObject(), 0}

void init(GUI *self);

void initLCD (void); 

void initUSART (void);

void uppdateQueue (GUI *self,int arg[2]);

#endif /* LCD_H_ */