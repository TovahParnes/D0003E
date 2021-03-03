/*
 * Lab-4.c
 *
 * Created: 2021-02-15 10:15:57
 * Author : Tovah
 */ 

#include "GUI.h"
#include "Button.h"
#include "TinyTimber.h"
#include "PulseGenerator.h"
#include "InputHandler.h"



int main(void)
{
	PortWriter		portWriter	 = initPortWriter();
	GUI				gui			 = initGUI();
	PulseGenerator	pG1		 = initPulseGenerator(&portWriter, &gui, 4, 80);
	PulseGenerator	pG2		 = initPulseGenerator(&portWriter, &gui, 6, 80);
	InputHandler	inputHandler = initInputHandler(&pG1, &pG2, &gui);
	
	INSTALL(&inputHandler, joystickHorizontal, IRQ_PCINT0);	// Left & Right
	INSTALL(&inputHandler, joystickVerticalPressed, IRQ_PCINT1);	// Up, Down & Pressed
	
	return TINYTIMBER(&inputHandler, initialize, NULL);
}