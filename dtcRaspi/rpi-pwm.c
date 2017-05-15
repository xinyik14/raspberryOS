#include "rpi-gpioclock.h"
#include "rpi-pwm.h"

volatile Pwm_registers* sysPwm = (Pwm_registers *) PWM_BASE;


void startPwmAudio(){
    
    volatile unsigned int count = 0;
    
    setGPIOAlt(4, 0);
    setGPIOAlt(12, 0);


    setGPIOClock(16, 0);

    sysPwm->ctl = 0;
    waitMicroSeconds(100);
    
    // sysPwm->dat1 = count++;
    sysPwm->ctl = PWM_CTL_PWEN1;

    while(1){
	    waitMicroSeconds(10000);
	    count += 100;
	    sysPwm->dat1 = count;    
    }

}

