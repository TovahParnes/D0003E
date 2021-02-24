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
	PulseGenerator	pG1		 = initPulseGenerator(&portWriter, &gui, 6);
	PulseGenerator	pG2		 = initPulseGenerator(&portWriter, &gui, 4);
	InputHandler	inputHandler = initInputHandler(&gui, &pG1, &pG2);
	
	return TINYTIMBER(&inputHandler, initialize, NULL);
}
/*
typedef struct {
	Object super;
	PortWriter *pw;
	GUI *gui;
	int pin, freq, savedFreq, isHigh;
} PulseGenerator;

#define initPulseGenerator(pw, gui, pin) \
{initObject(), pw, gui, pin, 0, 0, 0}
	*/