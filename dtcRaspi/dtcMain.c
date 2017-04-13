/*
    Reference: www.valvers.com
*/

#include <string.h>
#include <stdlib.h>

#include "rpi-gpio.h"
#include "rpi-systimer.h"


/** Main function - we'll never return from here */
void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{
    // test C-library
    unsigned int* counters;
    counters = malloc( 1024 * sizeof(unsigned int));
    if (counters == NULL){
	while(1) {
	    setGPIO(27, HIGH);
	}	
    }

    // test system timer
    while (1){
	waitMicroSeconds( 500000); // 0.5s
	setGPIO(27, HIGH);
	waitMicroSeconds(1000000); // 1s
	setGPIO(27, LOW);
    }
}
