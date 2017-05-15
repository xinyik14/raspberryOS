#include "rpi-serial.h"
#include "rpi-gpio.h"

volatile int mCkPin = 0;

int initSerial(int ckPin, int txPin, int rxPin){
    volatile int ret = 0;
    mCkPin = ckPin;
    ret = setGPIOMode(ckPin, INPUT);
    if (ret != 0) return -1;
    ret = setGPIOMode(txPin, OUTPUT);
    if (ret != 0) return -1;
    ret = setGPIOMode(rxPin, INPUT);
    if (ret != 0) return -1;
    ret = setGPIOEvent(ckPin, GPIO_EVENT_R);
    if (ret != 0) return -1;
    return 0;
}

int readSerial(void){
    volatile int ret = 0;
    while (!isGPIOEventDetected(mCkPin))
	;
    clearGPIOEvent(mCkPin);
    ret = 1;
    return ret;
}
