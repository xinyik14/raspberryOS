/*
    Reference: 
	Brian Sidebotham's Bare Metal Pi Tutorial. www.valvers.com
	Davis Welch's Pi Repo. www.github.com/dwelch67/raspberrypi
    
    
    Huanle Zhang at UC Davis. www.huanlezhang.com 
    Last Update: April 28, 2017

*/

#include <string.h>
#include <stdlib.h>

#include "rpi-gpio.h"
#include "rpi-systimer.h"
#include "rpi-interrupt.h"
#include "rpi-armtimer.h"
#include "rpi-core.h"

extern volatile int pCoreRun[];

void core0_main(void);
void timerTaskFunc(void);

void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{

    _disable_interrupts();

    setGPIO(27, HIGH);
    waitMicroSeconds(1000000);

    _enable_interrupts();
    
    startTimerTask(1000000, timerTaskFunc);

    start_core_1();
    start_core_2();
    start_core_3();

    core0_main();
}

void timerTaskFunc(void)
{
    static int lit = 0;
    if (lit){
	lit = 0;
	setGPIO(27, HIGH);
    } else {
	lit = 1;
	setGPIO(27, LOW);
    }
}

void core0_main(void)
{

    while (1){

    	waitMicroSeconds(500000);
	pCoreRun[1] = 1;

	waitMicroSeconds(500000);
	pCoreRun[1] = 0;

	waitMicroSeconds(500000);
	pCoreRun[2] = 1;

	waitMicroSeconds(500000);
	pCoreRun[2] = 0;

	waitMicroSeconds(500000);
	pCoreRun[3] = 1;

	waitMicroSeconds(500000);
	pCoreRun[3] = 0;
	
	
    }
 
}
