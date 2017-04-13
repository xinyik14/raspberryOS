#ifndef _SYSTIMER_H
#define _SYSTIMER_H

#define SYSTIMER_BASE 0x3F003000UL

typedef struct {
    volatile unsigned int control_status;
    volatile unsigned int counter_lo;
    volatile unsigned int counter_hi;
    volatile unsigned int compare0;
    volatile unsigned int compare1;
    volatile unsigned int compare2;
    volatile unsigned int compare3;
} Systimer_t;

void waitMicroSeconds(unsigned long long us);

#endif
