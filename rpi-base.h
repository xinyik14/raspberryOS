
#ifndef RPI_BASE_H
#define RPI_BASE_H

#include <stdint.h>

#ifdef RPI2
    #define PERIPHERAL_BASE     0x3F000000UL
#else
    #define PERIPHERAL_BASE     0x20000000UL
#endif
