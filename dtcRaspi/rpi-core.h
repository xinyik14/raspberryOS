/*
    Reference:
	Trying Bare Metal on Raspberry Pi 2. www.raspberrypi.org/forums/viewtopic.php?p=701773

    Huanle Zhang at UC Davis. www.huanlezhang.com
    Last Update: April 26, 2017
*/

#ifndef _RPI_CORE_H_
#define _RPI_CORE_H_

#define CORE1_START_ADDRESS 0x4000009C
#define CORE2_START_ADDRESS 0x400000AC
#define CORE3_START_ADDRESS 0x400000BC


void core_1_main(void);
void core_2_main(void);
void ocre_3_main(void);

extern volatile int pCoreRun[];

#endif
