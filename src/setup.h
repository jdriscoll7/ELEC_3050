#ifndef SETUP_H
#define SETUP_H

#include "STM32L1xx.h"


/* GPIOA and GPIOC clock enable definitions. */
#define GPIOA_RCC_EN 0x01
#define GPIOC_RCC_EN 0x04


/* Definitions for specific pin MODER modes. */
#define PA0_MODE_IN 0x00000003
#define PA1_MODE_IN 0x0000000C
#define PA2_MODE_IN 0x00000030
#define PA2_MODE_IN 0x00000030


/* Definitions for GPIOA input data registers. */
#define PA0_IDR (GPIOA->IDR & 0x01)
#define PA1_IDR (GPIOA->IDR & 0x02)
#define PA2_IDR (GPIOA->IDR & 0x04)


/* Hard-coded to setup specific pins. May be changed in future to allow parameters. */
void setup_pins(void);


/* Setup interrupt */
void setup_interrupts(void);


/* Interrupt service routines will go here. */


#endif
