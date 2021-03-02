/*
 * LCD.c
 *
 * Created: 2021-02-15 10:47:30
 *  Author: tovah
 */ 

#include <setjmp.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "GUI.h"

void writeChar(char ch, int pos){
	if (pos < 0 || pos > 5){
		return;
	}
	//Set the pointer to the address to the first position on the LCD
	uint8_t *addrLCD = (uint8_t *) 0xec;

	//Initiate the mask to get only one nibble of the number
	uint8_t mask;

	//Initiate the nibble to be sent to the display
	uint8_t nibbleNum = 0x0;

	//Initiate number to print;
	uint16_t num = 0x0;

	//Set SCC table to have the correct SCC values for the numbers 0-9 and a special character
	uint16_t tableSCC[11] = {0x1551, 0x0110, 0x1E11, 0x1B11, 0x0B50, 0x1B41, 0x1F41, 0x0111, 0x1F51, 0x0B51, 0xC028};

	//Check if the given character is in the interval 0-9 and set the right number value
	if (ch >= '0' && ch <= '9'){
		//Set the corresponding value from the table to the number
		num = tableSCC[ch - '0'];
		} else {
		//Set the special character from the table to the number
		num = tableSCC[10];
	}

	//Update the LCD address to the given position
	addrLCD += pos >> 1;

	//Set the correct mask if the position is even or odd
	if (pos % 2 == 0){
		mask = 0xF0;
		} else {
		mask = 0x0F;
	}

	//Place each of the four nibbles of the number on the LCD

	for (int i = 0; i < 4; i++){
		//Masking the smallest number to the current nibble
		nibbleNum = num & 0xF;
		//Remove the used nibble
		num = num >> 4;

		//Shift the nibble to the right position if the pos is odd
		if (pos % 2 != 0){
			nibbleNum = nibbleNum << 4;
		}

		//Write the current nibble to the LCD
		*addrLCD = (*addrLCD & mask) | nibbleNum;

		//Move to the next nibble sequence of the current digit on the LCD
		addrLCD += 5;
	}
}

void printAt(int pos, int num) {
	writeChar( (num % 100) / 10 + '0', pos);
	pos++;
	writeChar( num % 10 + '0', pos);
}

void changeCurrent(GUI *self, int arg){
	self->current = arg;
	printCurrent(self);
}

void printCurrent(GUI *self){
	if (self->current == 1){
		LCDDR1 = (1 << 0);
	} else if (self->current == 2){
		LCDDR1 = (1 << 4);
	}
}

void updateDisplayedFreq(GUI *self, int freq){
	int current = self->current;
	
	int pos = 2;
	if (current == 1){
		pos = 0;
	} else if (current == 2) {
		pos = 4;
	}
	printAt(pos, freq);
}

 void LCD_INIT(void){
	 // LCD
	 CLKPR = 0x80;
	 CLKPR = 0x00;
	 
	 //Set drive time to 300 milliseconds and contrast control voltage to 3.35 V
	 LCDCCR = (1 << LCDCC3) | (1 << LCDCC2) | (1 << LCDCC1) | (1 << LCDCC0);
	 
	 //Set external clock source, 1/3 bias, 1/4 duty cycle, 25 segments
	 LCDCRB = (1 << LCDCS) | (1 << LCDMUX1) | (1 << LCDMUX0) | (1 << LCDPM2) | (1 << LCDPM1) | (1 << LCDPM0);

	 //Set prescaler setting N=16 and clock divide settings D=8
	 LCDFRR = (1 << LCDCD2) | (1 << LCDCD1) | (1 << LCDCD0);

	 //Enable low power waveform, no frame interrupt, no blanking, LCD enable
	 LCDCRA = (1 << LCDAB) | (1 << LCDEN);
	 
	 asm("nop");
	 
	 LCDDR1 = (1 << 0);
	 writeChar('0', 0);
	 writeChar('0', 1);
	 writeChar('0', 4);
	 writeChar('0', 5);
 }
 
 void Button_INIT(void){
	 //Initialize for butterfly joystick
	 EIMSK = (1<<PCIE1) | (1<<PCIE0) | EIMSK;
	 
	 //Press down
	 PORTB = (1<<PB7) | PORTB;
	 PCMSK1 = (1<<PCINT15) | PCMSK1;
	 
	 //Press  upp
	 PORTB = (1<<PB6) | PORTB;
	 PCMSK1 = (1<<PCINT14) | PCMSK1;
	 
	 //Press right
	 PORTE = (1<<PE3) | PORTE;
	 PCMSK0 = (1<<PCINT3) | PCMSK0;
	 
	 //Press left
	 PORTE = (1<<PE2) | PORTE;
	 PCMSK0 = (1<<PCINT2) | PCMSK0;
	 
	 //Press in
	 PORTB = (1<<PB4) | PORTB;
	 PCMSK1 = (1<<PCINT12) | PCMSK1;
 }