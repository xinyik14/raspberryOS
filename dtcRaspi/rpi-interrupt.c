/*
    Reference: 
	Brian Sidebotham's Bare Metal Pi Tutorial. www.valvers.com
	Davis Welch's Pi Repo. www.github.com/dwelch67/raspberrypi
    
    
    Huanle Zhang at UC Davis. www.huanlezhang.com 
    April 26, 2017

*/

#include "rpi-interrupt.h"
#include "rpi-gpio.h"
#include "rpi-armtimer.h"


volatile Interrupt_registers* sysInterrupt = (Interrupt_registers *)
INTERRUPT_CONTROLLER_BASE;


void c_undefined_handler(void)
{
    // do nothing    
}

void c_swi_handler(void){
    
}

void c_prefetch_handler(void){
    
}

void c_data_handler(void){
    
}

void c_hyp_handler(void){
    
}

void c_irq_handler(void){
    
    _disable_interrupts();


    static int lit = 0;

    sysArmTimer->IRQ_ClearAck = 1;


	if ( lit ){
	    lit = 0;
	    while(setGPIO(27, HIGH) != 0)
		;	
	} else {
	   lit = 1;
	    while(setGPIO(27, LOW) != 0)
		;
	}
    
    _enable_interrupts();

}

void c_fiq_handler(void){
    
}
