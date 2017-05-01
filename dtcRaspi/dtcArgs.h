/*

    Huanle Zhang at UC Davis. www.huanlezhang.com
    Last Update: April 28, 2017

*/

#ifndef _DTC_ARGS_H_
#define _DTC_ARGS_H_


#define GPIO_BASE 0x3F200000UL

#define TIMER_BASE 0x3F00B000UL

#define INTERRUPT_BASE TIMER_BASE

#define SYSTIMER_BASE 0x3F003000UL

#define I2S_BASE ( GPIO_BASE + 0x3000 )

#define GPIO_CLOCK_BASE	0x3F101070UL

#endif
