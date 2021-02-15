/*
 * Button.c
 *
 * Created: 2021-02-15 11:14:39
 *  Author: tovah
 */ 

#include <setjmp.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "Button.h"


#define DISABLE()       cli()
#define ENABLE()        sei()

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
