/*
    Reference: 
	Brian Sidebotham's Bare Metal Pi Tutorial. www.valvers.com
	Davis Welch's Pi Repo. www.github.com/dwelch67/raspberrypi
    
    
    Huanle Zhang at UC Davis. www.huanlezhang.com 
    April 14, 2017

*/

#include "rpi-armtimer.h"

volatile Arm_timer_t* sysArmTimer = (Arm_timer_t*) ARMTIMER_BASE;



// nothing

