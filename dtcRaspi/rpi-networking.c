/*

    Huanle Zhang at UC Davis. www.huanlezhang.com
    Last Update: May 16, 2017

*/

#include "rpi-networking.h"
#include "rpi-serial.h"
#include "rpi-gpio.h"

static const int mCkPin = 2;
static const int mTxPin = 3;
static const int mRxPin = 4;

void startNetworking(void){
    
    int readData = 0;

    if (initSerial(mCkPin, mTxPin, mRxPin) == -1){
	setGPIO(14, HIGH);	
    }
    while (1){
	readData = readSerial();
	if (readData == 123){
	    setGPIO(16, HIGH);    
	} else {
	    setGPIO(16, LOW);    
	}
    }

}
