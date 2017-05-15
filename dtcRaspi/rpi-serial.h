#ifndef _RPI_SERIAL_H_
#define _RPI_SERIAL_H_

int initSerial(int ckPin, int txPin, int rxPin);
int readSerial(void);
#endif
