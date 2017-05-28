/*

    Huanle Zhang at UC Davis. www.huanlezhang.com
    Last Update: May 25, 2017

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dtcMediaPlayer.h"
#include "rpi-gpio.h"
#include "rpi-pwm.h"

volatile int pending_start = 0;
volatile int pending_stop = 0;
volatile int pending_prev = 0;
volatile int pending_next = 0;

volatile int pending_vol = 0;
volatile int volValue = 0;

int pMusicArray[PWM_BUFFER_SIZE];


inline void mediaPlayer_start(void){
    pending_start = 1;
}


inline void mediaPlayer_stop(void){
    pending_stop = 1;
}

inline void mediaPlayer_prev(void){
    pending_prev = 1;
}

inline void mediaPlayer_next(void){
    
    pending_next = 1;
}

inline void mediaPlayer_vol(int vol){
    pending_vol = 1;
    volValue = vol;
}

void startMediaPlayer(void){

    int size_buffer = 0;
    int i = 0;
    char data = 0;


    while (pwmInitialized() == -1)
	;
    
    setGPIO(6, HIGH);

    for (i = 0; i < PWM_BUFFER_SIZE; i++){
	pMusicArray[i] = rand() % 256; 
    }
    pwmInitializeBuffer(pMusicArray);

    while(1){
	if (pending_start != 0){
	    pending_start = 0;

	    setGPIO(13, HIGH);    
	    pwmResume();
	    continue;
	}
	if (pending_stop != 0){
	    pending_stop = 0;
	    setGPIO(13, LOW);

	    pwmStop();
	    continue;
	}
	if (pending_prev != 0){
	    pending_prev = 0;
	    setGPIO(19, HIGH); 
	    continue;
	}
	if (pending_next != 0){
	    pending_next = 0;
	    setGPIO(19, LOW);
	    continue;
	}
	if (pending_vol != 0){
	    pending_vol = 0;
	    // pwmSetVol(volValue / 63.0);
	    continue;
	}

	if (pwmBufferWritable() == 1){
	    for (i = 0; i < PWM_BUFFER_SIZE/2; i++){
		pMusicArray[i] = rand() % 256;
	    }
	    pwmAddData(pMusicArray);    
	}

    }    
}
