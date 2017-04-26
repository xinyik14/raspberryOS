/*
    Reference: 
	Brian Sidebotham's Bare Metal Pi Tutorial. www.valvers.com
	Davis Welch's Pi Repo. www.github.com/dwelch67/raspberrypi
    
    
    Huanle Zhang at UC Davis. www.huanlezhang.com 
    Last Update: April 26, 2017

*/

#include <string.h>
#include <stdlib.h>

#include "rpi-gpio.h"
#include "rpi-systimer.h"
#include "rpi-interrupt.h"
#include "rpi-armtimer.h"
#include "rpi-core.h"

extern  _core_1_main;
extern  _core_2_main;
extern  _core_3_main;
volatile unsigned int* pCore;

extern volatile int pCoreRun[];

void core0_main(void);

/** Main function - we'll never return from here */
void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{

    _disable_interrupts();

    // test C-library
    unsigned int* counters;
    counters = malloc( 1024 * sizeof(unsigned int));
    if (counters == NULL){
	setGPIO(17, HIGH);
	while(1)
	    ;
    }

    setGPIO(27, HIGH);
    waitMicroSeconds(1000000);


    sysInterrupt->base_disable = INTERRUPT_TABLE_ARM_TIMER;
    sysArmTimer->Load = 1000000-1;
    sysArmTimer->Reload = 1000000-1;
    sysArmTimer->IRQ_ClearAck= 1;
    sysArmTimer->Control= ARMTIMER_CONTROL_23BIT |
    ARMTIMER_CONTROL_PRESCALE_1 | ARMTIMER_CONTROL_TIMER_INTERRUPT_ENABLE |
    ARMTIMER_CONTROL_TIMER_ENABLE;
    
    sysInterrupt->base_interrupt_enable = INTERRUPT_TABLE_ARM_TIMER;
 

    pCore = (unsigned int*) CORE1_START_ADDRESS;
    *pCore = (unsigned int) &_core_1_main;
    pCore = (unsigned int*) CORE2_START_ADDRESS;
    *pCore = (unsigned int) &_core_2_main;
    pCore = (unsigned int*) CORE3_START_ADDRESS;
    *pCore = (unsigned int) &_core_3_main;

    _enable_interrupts();
    core0_main();
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
