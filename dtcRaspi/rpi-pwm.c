/*

    Reference:
	Accessing the hardware pwm peripheral on the raspberry pi in c++.
	www.hertaville.com/rpipwm.html


    Huanle Zhang at UC Davis. www.huanlezhang.com
    Last Update: May 27, 2017

*/

#include "rpi-gpioclock.h"
#include "rpi-pwm.h"
#include "rpi-gpio.h"

volatile Pwm_registers* sysPwm = (Pwm_registers *) PWM_BASE;

volatile static int pData[PWM_BUFFER_SIZE];
volatile static int writeIndex = PWM_BUFFER_SIZE/2, playIndex = 0;
volatile static int status = -1; // -1 - not start; 0 - start; 1 - stop
volatile static double volScale = 1.0;


volatile static int nCount = 0;
volatile static int bWritable = 0;

void pwmInitializeBuffer(int* dataArray){
    int i = 0;
    for (i = 0; i < PWM_BUFFER_SIZE; i++){
	pData[i] = dataArray[i];	
    }
}

void pwmAddData(int* dataArray){
    int i = 0;
    for (i = 0; i < PWM_BUFFER_SIZE/2; i++){
	pData[writeIndex] = dataArray[i];
	writeIndex = (writeIndex + 1) % PWM_BUFFER_SIZE;
    }
    bWritable = 0;
}

inline int pwmBufferWritable(void){
    return bWritable;
}

inline int pwmInitialized(void){
   return status; 
}

inline void pwmStop(void){
    status = 1;
}

inline void pwmResume(void){
    status = 0;    
}

inline void pwmSetVol(double volRatio){
    volScale = volRatio;    
}

void startPwmAudio(){

    char data = 0;
    
    setGPIOAlt(12, 0);
   
    setGPIOClock(2, 0); // maximum frequency 37.5K, 256 resolution

    sysPwm->ctl = 0;
    sysPwm->rng1 = 256;
    sysPwm->dat1 = 128;
    sysPwm->ctl |= PWM_CTL_PWEN1;
    
    status = 1;
    

    while (1){

	if(status == 1){ // stop
	    waitMicroSeconds(10);
	    continue;    
	}
	waitMicroSeconds(100000);
	
	// sysPwm->dat1 =  ((int)(volScale * pData[playIndex])) % 256;
	if (nCount % 2 == 0){
	    sysPwm->dat1 = 0;    
	} else {
	    sysPwm->dat1 = 255;
	}
	playIndex = (playIndex + 1) % PWM_BUFFER_SIZE;
	nCount++;
	if (nCount >= PWM_BUFFER_SIZE / 2){
	    nCount = 0;
	    bWritable = 1;
	}
    }
}

