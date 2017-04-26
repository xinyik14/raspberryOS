/*
    Reference:
	Trying Bare Metal on Raspberry Pi 2. www.raspberrypi.org/forums/viewtopic.php?p=701773


    Huanle Zhang at UC Davis. www.huanlezhang.com
    Last Update: April 26, 2017

*/

#include "rpi-core.h"
#include "rpi-gpio.h"

volatile int pCoreRun[4] = {0, 0, 0, 0};

void core_1_main(void){
    
    volatile static int ledStatus = 0;

    while(1){
	while (pCoreRun[1] == ledStatus)
	    ;
	ledStatus = pCoreRun[1];
	if (ledStatus == 0){
	    setGPIO(17, LOW);    
	} else if (ledStatus == 1){
	    setGPIO(17, HIGH);    
	}
    }

}

void core_2_main(void){

    volatile static int ledStatus = 0;

    while(1){
	while (pCoreRun[2] == ledStatus)
	    ;
	ledStatus = pCoreRun[2];
	if (ledStatus == 0){
	    setGPIO(22, LOW);    
	} else if (ledStatus == 1){
	    setGPIO(22, HIGH);    
	}
    }
}


void core_3_main(void){
    
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

