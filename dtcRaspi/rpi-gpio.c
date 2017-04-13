#include "rpi-gpio.h"

const int gpio_pin[][2] = { // #register, #bit
  {0, 0}, // pin 0
  {0, 3}, // pin 1
  {0, 6}, // pin 2
  {0, 9}, // pin 3
  {0, 12}, // pin 4
  {0, 15}, // pin 5
  {0, 18}, // pin 6
  {0, 21}, // pin 7
  {0, 24}, // pin 8
  {0, 27}, // pin 9
  {1, 0}, // pin 10
  {1, 3}, // pin 11
  {1, 6}, // pin 12
  {1, 9}, // pin 13
  {1, 12}, // pin 14
  {1, 15}, // pin 15
  {1, 18}, // pin 16
  {1, 21}, // pin 17
  {1, 24}, // pin 18
  {1, 27}, // pin 19
  {2, 0}, // pin 20
  {2, 3}, // pin 21
  {2, 6}, // pin 22
  {2, 9}, // pin 23
  {2, 12}, // pin 24
  {2, 15}, // pin 25
  {2, 18}, // pin 26
  {2, 21}, // pin 27
  {2, 24}, // pin 28
  {2, 27}, // pin 29
  {3, 0}, // pin 30
  {3, 3}, // pin 31
  {3, 6}, // pin 32
  {3, 9}, // pin 33
  {3, 12}, // pin 34
  {3, 15}, // pin 35
  {3, 18}, // pin 36
  {3, 21}, // pin 37
  {3, 24}, // pin 38
  {3, 27}, // pin 39
  {4, 0}, // pin 40
  {4, 3}, // pin 41
  {4, 6}, // pin 42
  {4, 9}, // pin 43
  {4, 12}, // pin 44
  {4, 15}, // pin 45
  {4, 18}, // pin 46
  {4, 21}, // pin 47
  {4, 24}, // pin 48
  {4, 27}, // pin 49
  {5, 0}, // pin 50
  {5, 3}, // pin 51
  {5, 6}, // pin 52
  {5, 9}, // pin 53
};

volatile unsigned int* gpio = (unsigned int*)GPIO_BASE;

int setGPIO(int pin, int status){
    
    unsigned int bitValue;

    if (pin < 0 || pin > 53) return -1;
    if (status != HIGH && status != LOW) return -2;

    bitValue = gpio[GPIO_GPFSEL0 + gpio_pin[pin][0]] & (1 <<
    (gpio_pin[pin][1]+2));
    if (bitValue != 0){
	gpio[GPIO_GPFSEL0 + gpio_pin[pin][0]] &= ~(1 <<
	(gpio_pin[pin][1]+2));	
    }
    bitValue = gpio[GPIO_GPFSEL0 + gpio_pin[pin][0]] & (1 <<
    (gpio_pin[pin][1]+1));
    if (bitValue != 0){
	gpio[GPIO_GPFSEL0 + gpio_pin[pin][0]] &= ~(1 <<
	(gpio_pin[pin][1]+1));	
    }
    bitValue = gpio[GPIO_GPFSEL0 + gpio_pin[pin][0]] & (1 <<
    (gpio_pin[pin][1]));
    if (bitValue == 0){
	gpio[GPIO_GPFSEL0 + gpio_pin[pin][0]] |= (1 <<
	(gpio_pin[pin][1]));	
    }
    
    if (status == HIGH){
	if (pin <= 31){
	    gpio[GPIO_GPSET0] |= (1 << pin);
	} else {
	    gpio[GPIO_GPSET1] |= (1 << (pin - 32));    
	}
    } else {
	if (pin <= 31){
	    gpio[GPIO_GPCLR0] |= (1 << pin);    
	} else {
	    gpio[GPIO_GPCLR1] |= (1 << (pin -32));
	}
    }
    return 0;
}
