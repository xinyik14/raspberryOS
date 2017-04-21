/*
    Reference:
	Trying Bare Metal on Raspberry Pi 2. www.raspberrypi.org/forums/viewtopic.php?p=701773


    Huanle Zhang at UC Davis. www.huanlezhang.com
    Last Update: April 21, 2017

*/

#include "rpi-core.h"
#include "rpi-gpio.h"

void core_1_main(void){
    
    volatile int i = 0;
    while(1){
	for(i = 0; i < 500000; i++){
	    //setGPIO(17, HIGH);    
	}
	setGPIO(17, HIGH);
	for (i = 0; i < 500000; i++){
	    //setGPIO(17, LOW);    
	}
	setGPIO(17, LOW);
    }

}

void core_2_main(void){
     
    volatile int i = 0;
    while(1){
	for(i = 0; i < 500000; i++){
	    //setGPIO(5, HIGH);    
	}
	setGPIO(5, HIGH);
	for (i = 0; i < 500000; i++){
	    // setGPIO(5, LOW);    
	}
	setGPIO(5, LOW);
    }

}

void core_3_main(void){
    
    volatile int i = 0;
    while(1){
	for(i = 0; i < 500000; i++){
	   // setGPIO(10, HIGH);    
	}
	setGPIO(10, HIGH);
	for (i = 0; i < 500000; i++){
	    //setGPIO(10, LOW);    
	}
	setGPIO(10, LOW);
    }


}

