/*
 * Lab-4.c
 *
 * Created: 2021-02-15 10:15:57
 * Author : Tovah
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include "LCD.h"
#include "Button.h"
#include "TinyTimber.h"

int main(void)
{
    LCD_INIT();
    Button_INIT();
    while (1) 
    {
		printAt(12345, 0);
    }
}

