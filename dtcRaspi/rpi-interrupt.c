/*
    Reference: 
	Brian Sidebotham's Bare Metal Pi Tutorial. www.valvers.com
	Davis Welch's Pi Repo. www.github.com/dwelch67/raspberrypi
    
    
    Huanle Zhang at UC Davis. www.huanlezhang.com 
    April 14, 2017

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
    
    static int lit = 0;

    sysArmTimer->IRQ_ClearAck = 1;

    if ( lit ){
	lit = 0;
	setGPIO(27, HIGH);	
    } else {
	lit = 1;
	setGPIO(27, LOW);
    }

}

void c_fiq_handler(void){
    
}
