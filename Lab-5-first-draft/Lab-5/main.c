/*
 * Lab-5.c
 *
 * Created: 2021-03-04 09:26:13
 * Author : Adam Hedberg
 */ 

#include <avr/io.h>
#include "GUI.h"
#include "Controller.h"
#include "OutputHandler.h"
#include "InputHandler.h"
#include "TinyTimber.h"

int main(void)
{
 
  GUI gui = initGUI();
  
  OutputHandler opH = initOutputHandler();
  
  Controller controller = initController(&opH, &gui);

  InputHandler inputHandler = initInputHandler(&controller, &gui);
  
  INSTALL (&inputHandler, &sensorInterupt, IRQ_USART0_RX);
  
  return TINYTIMBER(&controller, initialize, NULL);

	
}

