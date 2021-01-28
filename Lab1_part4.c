/*
 * D0003E-lab1.c
 *
 * Created: 2021-01-25 09:37:43
 * Author : adahed-8
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

void LCDInit(void){
	//Set drive time to 300 milliseconds and contrast control voltage to 3.35 V
	LCDCCR = (1 << LCDCC3) | (1 << LCDCC2) | (1 << LCDCC1) | (1 << LCDCC0);
	
	//Set external clock source, 1/3 bias, 1/4 duty cycle, 25 segments
	LCDCRB = (1 << LCDCS) | (1 << LCDMUX1) | (1 << LCDMUX0) | (1 << LCDPM2) | (1 << LCDPM1) | (1 << LCDPM0);
	
	//Set prescaler setting N=16 and clock divide settings D=8
	LCDFRR = (1 << LCDCD2) | (1 << LCDCD1) | (1 << LCDCD0);
	
	//Enable low power waveform, no frame interrupt, no blanking, LCD enable
	LCDCRA = (1 << LCDAB) | (1 << LCDEN);
}

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

void writeLong(long i){
	//loop for the last six digits of the number
	for (int pos = 5; pos >= 0; pos--){
		//Return from function if the given number is shorter than 6 digits
		if (i < 1){
			return;
		}
		
		//Write the smallest digits using writeChar
		writeChar((i % 10) + '0', pos);
		//Remove the used smallest digit
		i = i/10;
	}
}

int is_prime(long i){
	//Check if the given long has any prime factors
	for(int n = 2; n < i; n++){
		if (i % n == 0){
			return 0;
		}
	
	}
	return 1;
}

void primes(void){
	for (long i = 3; i < 10000; i++){
		if (is_prime(i) == 1){
			writeLong(i);
		}
	}
}

void blink(void){
	//Set prescaling factor to 256
	TCCR1B = (1 << CS12);
	
	// variable for the middle between 0x0000 and 0xFFFF
	uint16_t middle = 0x7FFF;

	while (true){
		//If the timer is in the middle, turn off the display
		if (TCNT1 == middle){
			LCDDR18 = 0x0;
			
		//If the times is at the begining, turn on the display
		} else if (TCNT1 == 0) {
			LCDDR18 = 0x1;
		}
	}
}


void button(void){
	// Activate the pull-upp register for bit 7
	PORTB = (1<<PB7) | PORTB;

	//Flag for if the LCD bit is on
	bool onFlag = false;
	//Flag for if the joystick is down
	bool down = false;
	
	while (true){
		down = false;
		//Loop for the duration that the joystick is pressed down
		while (( PINB & 1<<PB7) == 0){
			//Run only on the first loop of being pressed down
			if(!down){
				down = true;
				//If the LCD bit is off, turn it on
				if(!onFlag){
					LCDDR13 = 0x1;
					onFlag = true;
				//If the LCD bit is on, turn it off
				} else {
					LCDDR13 = 0x0;
					onFlag = false;
				}
			}
		}
	}
}

void combined(void){
	long nextNum = 3;
	//long maxPrime = 100000;
	
	//Set prescaling factor to 256
	TCCR1B = (1 << CS12);
	// variable for the middle between 0x0000 and 0xFFFF
	uint16_t middle = 0x7FFF;
	
	// Activate the pull-upp register for bit 7
	PORTB = (1<<PB7) | PORTB;
	//Flag for if the LCD bit is on
	bool onFlag = false;
	//Flag for if the joystick is down
	bool down = false;
	
	while (true){
		
		//_____Prime_____
		//Case 1: calculate next prime without interruptions
		/*
		for (long i = nextNum; i < maxPrime; i++){
			if (is_prime(i) == 1){
				nextNum = i+1;
				writeLong(i);
				break;
			}
		}*/
		
		//Case 2: calculate if next number is a prime without interruptions
		if (is_prime(nextNum) == 1){
			writeLong(nextNum);
		}
		nextNum++;
		
		//_____Blink_____
		//If the timer is in the middle, turn off the display
		if (TCNT1 >= middle){
			LCDDR18 = 0x0;
		//If the times is at the beginning, turn on the display
		} else if (TCNT1 <= middle) {
			LCDDR18 = 0x1;
		}
		
		
		//_____Button_____
		//Case 1
		/*
		down = false;
		//Loop for the duration that the joystick is pressed down
		while (( PINB & 1<<PB7) == 0){
			//Run only on the first loop of being pressed down
			if(!down){
				down = true;
				//If the LCD bit is off, turn it on
				if(!onFlag){
					LCDDR13 = 0x1;
					onFlag = true;
					//If the LCD bit is on, turn it off
					} else {
					LCDDR13 = 0x0;
					onFlag = false;
				}
			}
		}*/
		
		//Case 2
		if ((PINB & 1<<PB7) == 0)
		{
			down = true;
		} else {
			down = false;
		}
		
		if(!down){
			//If the LCD bit is off, turn it on
			if(!onFlag){
				LCDDR13 = 0x1;
				onFlag = true;
				//If the LCD bit is on, turn it off
				} else {
				LCDDR13 = 0x0;
				onFlag = false;
			}
		}
	}
	
}


int main(void)
{
	//Disable CPU clock prescaler functionality
	CLKPR = 0x80;
	CLKPR = 0x00;
	
	LCDInit();

	//writeLong(1234567890);		//Max 10 digit numbers
	//primes();
	//button();
	//blink();
	
	combined();
}

