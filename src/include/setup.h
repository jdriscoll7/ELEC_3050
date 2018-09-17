/* - File: setup.h 

       - Description
           - Provides definitions and function declarations that make 
             setting up essential parts of a project up, including pin and
             interrupt definitions and functions, easier.
             
       - Author: Joe Driscoll 
*/


#ifndef SETUP_H
#define SETUP_H


#include "STM32L1xx.h"
#include "timing_functions.h"
#include "interrupt_handlers.h"
#include "keypad_driver.h"
#include <stdint.h>


/* GPIOA and GPIOC clock enable definitions. */
#define RCC_AHBENR   (RCC->AHBENR)
#define GPIOA_RCC_EN 0x01
#define GPIOC_RCC_EN 0x04


/* GPIO definitions. */
#define GPIOA_MODER     (GPIOA->MODER)
#define GPIOC_MODER     (GPIOC->MODER)
#define PC70_DOUT_SET   (0x5555)            /* Bits to set for PC[7:0] MODER (output). */
#define PC70_DOUT_CLR   (~0x0000AAAA)       /* Bits to clear for PC[7:0] MODER (output). */
#define PC98_DOUT_SET   (0x05 << (2*8))     /* Bits to set for PC[9:8] MODER (output). */
#define PC98_DOUT_CLR   (~(0x0A << (2*8)))  /* Bits to clear for PC[9:8] MODER (output). */


/* Definitions for specific pin MODER modes. */
#define P0_MODE_INPUT 0x00000003
#define P1_MODE_INPUT 0x0000000C
#define P2_MODE_INPUT 0x00000030


/* Definitions for GPIOA input data registers. */
#define PA0_IDR ((uint16_t) (GPIOA->IDR & 0x01))
#define PA1_IDR ((uint16_t) (GPIOA->IDR & 0x02))
#define PA2_IDR ((uint16_t) (GPIOA->IDR & 0x04))


/* GPIOC ODR for reading LED states. */
#define PC8_ODR ((uint16_t) (GPIOC->ODR & 0x100))
#define PC9_ODR ((uint16_t) (GPIOC->ODR & 0x200))


/* Interrupt setup definitions. */
#define SYSCFG_EXTICR1   (SYSCFG->EXTICR[0])
#define EXTI_IMR         (EXTI->IMR)
#define EXTI_FTSR        (EXTI->FTSR)
#define EXTI_RTSR        (EXTI->RTSR)
#define EXTICRn_PA(x)    ((uint32_t) (0xF << (4*(x))))
#define EXTICRn_PA_EN(x) ((uint32_t) (0x0 << (4*(x))))
#define EXTI0_IMR_MASK   ((uint32_t) 0x01)
#define EXTI1_IMR_MASK   ((uint32_t) 0x02)
#define EXTI_EDGE_EN(n)  ((uint32_t) (0x01 << (n)))


/* Hard-coded to setup specific pins. May be changed in future to allow parameters. */
void setup_pins(void);


/* Sets up PA0 and PA1 as interrupts. */
void setup_interrupts(void);


#endif
