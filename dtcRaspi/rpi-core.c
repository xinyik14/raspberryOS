/*
    Reference:
	Trying Bare Metal on Raspberry Pi 2. www.raspberrypi.org/forums/viewtopic.php?p=701773


    Huanle Zhang at UC Davis. www.huanlezhang.com
    Last Update: May 16, 2017

*/

#include "rpi-core.h"
#include "rpi-gpio.h"
#include "rpi-i2s.h"
#include "rpi-pwm.h"
#include "rpi-serial.h"
#include "rpi-networking.h"

volatile int pCoreRun[4] = {0, 0, 0, 0};

volatile unsigned int* pCore;

void start_core_1(void){
    pCore = (unsigned int*) CORE1_START_ADDRESS;
    *pCore = (unsigned int) &_core_1_main;
}

void start_core_2(void){
    pCore = (unsigned int*) CORE2_START_ADDRESS;
    *pCore = (unsigned int) &_core_2_main;
}

void start_core_3(void){
    pCore = (unsigned int*) CORE3_START_ADDRESS;
    *pCore = (unsigned int) &_core_3_main;
    
}

void core_1_main(void){
    
    // for networking

    startNetworking();

}

void core_2_main(void){
    
    while (1){
	waitMicroSeconds(500000);
	setGPIO(17, HIGH);
	waitMicroSeconds(500000);
	setGPIO(17, LOW);
    }
}


void core_3_main(void){

    startPwmAudio();
//    startAudio();

    volatile static int ledStatus = 0;

    while(1){
	while (pCoreRun[3] == ledStatus)
	    ;
	ledStatus = pCoreRun[3];
	if (ledStatus == 0){
	    setGPIO(5, LOW);    
	} else if (ledStatus == 1){
	    setGPIO(5, HIGH);    
	}
    }
}

