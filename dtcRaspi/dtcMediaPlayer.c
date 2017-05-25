/*

    Huanle Zhang at UC Davis. www.huanlezhang.com
    Last Update: May 25, 2017

*/

#include "dtcMediaPlayer.h"
#include "rpi-gpio.h"

volatile int pending_start = 0;
volatile int pending_stop = 0;
volatile int pending_prev = 0;
volatile int pending_next = 0;

volatile int pending_vol = 0;
volatile int volValue = 0;

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
    while(1){
	if (pending_start != 0){
	    pending_start = 0;
	    setGPIO(6, HIGH);    
	}
	if (pending_stop != 0){
	    pending_stop = 0;
	    setGPIO(6, LOW);
	}
	if (pending_prev != 0){
	    pending_prev = 0;
	    //
	}
	if (pending_next != 0){
	    pending_next = 0;
	    //
	}
	if (pending_vol != 0){
	    pending_vol = 0;
	    //
	}
    }    
}
