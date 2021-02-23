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

PortWriter		portWriter	 = initPortWriter();
GUI				gui			 = initGUI();
PulseGenerator	pG1		 = initPulseGenerator(&portWriter, &gui, 4);
PulseGenerator	pG2		 = initPulseGenerator(&portWriter, &gui, 6);
InputHandler	inputHandler = initInputHandler(&gui, &pG1, &pG2);

int main(void)
{
	return TINYTIMBER(&inputHandler, initialize, NULL);
}

