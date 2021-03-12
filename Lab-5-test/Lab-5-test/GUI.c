/*
 * GUI.c
 *
 * Created: 2021-03-12 10:44:56
 *  Author: adahed-8
 */ 

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include "GUI.h"
#include "state.h"


static struct termios oldTerminalSettings, prgmTerminalSettings;

void *draw(void *arg){
	
}

void initGUI(void) {
	printf("Init GUI\n");
	/*
	// Get settings of stdin
	tcgetattr(STDIN_FILENO, &oldTerminalSettings);

	// Copy settings 
	prgmTerminalSettings = oldTerminalSettings;

	// Set new terminal attributes
	prgmTerminalSettings.c_lflag &= ~(ICANON) // Disable input buffer until endl or EOF
	&  ~(ECHO);  // Don't echo back typed keys

	prgmTerminalSettings.c_cc[VMIN] = 0;      //
	prgmTerminalSettings.c_cc[VTIME] = 1;     // These two sets polling read

	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

	//Set new terminal settings
	tcsetattr(STDIN_FILENO, TCSANOW, &prgmTerminalSettings);

	runTUI = 1;
	sem_init(&tuiSem, 0, 0);

	CLEAR();
	//printf("\x1B[35;1H%10d%10d", prgmTerminalSettings.c_cc[VMIN], prgmTerminalSettings.c_cc[VTIME]);

	drawBridge();
	//printf("here\n");
	//draw();
	*/
}