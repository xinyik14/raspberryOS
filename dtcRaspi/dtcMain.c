#include "rpi-gpio.h"

volatile unsigned int tim;

/** Main function - we'll never return from here */
void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{
    while (1){
	for (tim = 0; tim < 500000; tim++)
	    ;
	setGPIO(27, HIGH);
	
	for (tim = 0; tim < 1500000; tim++)
	    ;
	setGPIO(27, LOW);
    }

}
