/*

    under testing ... 

*/



#include <limits.h>
#include <math.h>
#include "rpi-i2s.h"
#include "rpi-gpio.h"
#include "rpi-gpioclock.h"

void play();

volatile PCM_registers* sysPcm = (PCM_registers *)  I2S_BASE;

const int FS = 48000;
int mOutFreq = 440;

void startAudio(){

    // 48 Hz


     setGPIOAlt(4, 0);

    setGPIOClock(12, 512); 
    
/*
    sysClockManager->ctl = 0x5A000000 | 1;
    while (sysClockManager->ctl & ( 1 << 7))
	;
    sysClockManager->div = 0x5A000000 | (0xfff << 12) | (0xfff << 0);
    sysClockManager->ctl = 0x5A000010 | 1;
*/
    //sysClockManager->ctl = (0x5a << 24) | (1 << 9) | (1 << 0);
    //sysClockManager->div = (0x5a << 24) | ( 0xfff << 12 ) | (0xfff << 0);
    //sysClockManager->ctl |= (0x5a) | (1 << 4);

    setGPIOAlt(PCM_CLK, PCM_CLK_GPIO_ALT);
    setGPIOAlt(PCM_FS, PCM_FS_GPIO_ALT);
    setGPIOAlt(PCM_DIN, PCM_DIN_GPIO_ALT);
    setGPIOAlt(PCM_DOUT, PCM_DOUT_GPIO_ALT);

    // frame length, frame sync length, 32bit
    sysPcm->cs = PCM_CS_EN;
    sysPcm->cs |= PCM_CS_RXERR | PCM_CS_TXERR | PCM_CS_RXCLR | PCM_CS_TXCLR;
    sysPcm->mode = (1 << PCM_MOD_FLEN_BIT) | (1 << PCM_MOD_FSLEN_BIT);
    sysPcm->txc = PCM_TXC_CH1WEX | PCM_TXC_CH1EN | (0xF << PCM_TXC_CH1WID_BIT);
    sysPcm->cs |= PCM_CS_SYNC;

    while ((sysPcm->cs & PCM_CS_SYNC) == 0)
	;
    setGPIO(5, HIGH);
    // sysPcm->cs |= (2 << PCM_CS_TXTHR_BIT);

    sysPcm->fifo = UINT_MAX;
    // enable transmit
    sysPcm->cs = PCM_CS_TXON;

    play();
}

void play(){
    double ph = 0.0;
    static unsigned int fifoData = UINT_MAX;
    while (1){
	if ((sysPcm->cs & PCM_CS_TXW) != 0){
	    // transmit data
	    // fifoData = (unsigned int)(UINT_MAX/2.0 * (1+dtcCos(ph)));
	    fifoData--;
	    ph += 2.0 * M_PI * mOutFreq / FS;
	    sysPcm->fifo = fifoData;
	}
    }

}
