#ifndef SETUP_H
#define SETUP_H

#include "STM32L1xx.h"


/* Definitions for switch_1 and switch_2 input data. */
#define PA1_IDR (GPIOA->IDR & 0x02)
#define PA2_IDR (GPIOA->IDR & 0x04)


/* Hard-coded to setup specific pins. May be changed in future to allow parameters. */
void setup_pins(void);


#endif
