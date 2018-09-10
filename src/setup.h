#ifndef SETUP_H
#define SETUP_H

#include "STM32L1xx.h"
#include "timing_functions.h"
#include "interrupt_handlers.h"
#include <stdint.h>


/* GPIOA and GPIOC clock enable definitions. */
#define GPIOA_RCC_EN 0x01
#define GPIOC_RCC_EN 0x04


/* Definitions for specific pin MODER modes. */
#define P0_MODE_INPUT 0x00000003
#define P1_MODE_INPUT 0x0000000C
#define P2_MODE_INPUT 0x00000030


/* Definitions for GPIOA input data registers. */
#define PA0_IDR (GPIOA->IDR & 0x01)
#define PA1_IDR (GPIOA->IDR & 0x02)
#define PA2_IDR (GPIOA->IDR & 0x04)


/* Interrupt setup definitions. */

#define EXTICRn_PA(x)    ((uint32_t) (0xF << (4*(x))))
#define EXTICRn_PA_EN(x) ((uint32_t) (0x0 << (4*(x))))
#define SYSCFG_EXTICR1   (SYSCFG->EXTICR[0])


/* Hard-coded to setup specific pins. May be changed in future to allow parameters. */
void setup_pins(void);


/* Sets up PA0 and PA1 as interrupts. */
void setup_interrupts(void);


#endif
