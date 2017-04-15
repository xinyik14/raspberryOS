/*
    Reference: 
	Brian Sidebotham's Bare Metal Pi Tutorial. www.valvers.com
	Davis Welch's Pi Repo. www.github.com/dwelch67/raspberrypi
    
    
    Huanle Zhang at UC Davis. www.huanlezhang.com 
    April 14, 2017

*/

#include <string.h>
#include <stdlib.h>

#include "rpi-gpio.h"
#include "rpi-systimer.h"
#include "rpi-interrupt.h"
#include "rpi-armtimer.h"


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

    setGPIO(27, HIGH);
    waitMicroSeconds(2000000);

    sysInterrupt->base_disable = INTERRUPT_TABLE_ARM_TIMER;
    
    sysArmTimer->Load = 1000000-1;
    sysArmTimer->Reload = 1000000-1;
    sysArmTimer->IRQ_ClearAck= 1;
    sysArmTimer->Control= ARMTIMER_CONTROL_23BIT |
    ARMTIMER_CONTROL_PRESCALE_1 | ARMTIMER_CONTROL_TIMER_INTERRUPT_ENABLE |
    ARMTIMER_CONTROL_TIMER_ENABLE;
    
    sysInterrupt->base_interrupt_enable = INTERRUPT_TABLE_ARM_TIMER;
    _enable_interrupts();
    
    while(1) continue;


}
