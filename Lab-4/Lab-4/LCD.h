/*
 * LCd.h
 *
 * Created: 2021-02-15 10:47:42
 *  Author: tovah
 */ 


#ifndef LCD_H_
#define LCD_H_

struct LCD_block;

void LCD_INIT(void);
void printAt(long, int);

#endif /* LCD_H_ */