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

void LCD_INIT(void);

void Button_INIT(void);

void changeCurrent(GUI *self, int arg);

void updateDisplayedFreq(GUI *self, int freq);

#endif /* LCD_H_ */