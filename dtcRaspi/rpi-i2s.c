/*

    under testing ... 

*/



#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>

#include "rpi-i2s.h"
#include "dtcMath.h"

void play();

volatile PCM_registers* sysPcm = (PCM_registers *)  I2S_BASE;

volatile Clock_manager* sysClockManager = (Clock_manager *) GPIO_CLOCK_BASE;

const int FS = 48000;
int mOutFreq = 440;

void startAudio(){

    // 48 Hz
    sysClockManager->div = ( 12 << 12 ) | (512 << 0);
    sysClockManager->ctl = (1 << 9) | (1 << 4) | (1 << 0);

    // clock set
    
    // wait 4 PCM clocks
    /*
    sysPcm->cs &= ~( PCM_CS_SYN );
    while ((sysPcm->cs & PCM_CS_SYN) != 0)
	;
    sysPcm->cs |= PCM_CS_SYN;
    while ((sysPcm->cs & PCM_CS_SYN) == 0)
	;
    */


    // frame length, frame sync length, 32bit
    sysPcm->mode = (0x1F << PCM_MOD_FLEN_BIT) | (0x1F << PCM_MOD_FSLEN_BIT);

    sysPcm->txc = PCM_TXC_CH1WEX | PCM_TXC_CH1EN | (0xF << PCM_TXC_CH1WID_BIT);

    // enable transmit
    sysPcm->cs = PCM_CS_TXON | PCM_CS_EN;
    play();
}

void play(){
    double ph = 0.0;
    unsigned int fifoData;
    while (1){
	if ((sysPcm->cs & PCM_CS_TXW) != 0){
	    // transmit data
	    fifoData = (unsigned int)(UINT_MAX/2.0 * (1+dtcCos(ph)));
	    ph += 2.0 * M_PI * mOutFreq / FS;
	    sysPcm->fifo = fifoData;
	}
    }

}
