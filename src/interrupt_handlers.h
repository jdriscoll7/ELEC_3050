#ifndef INTERRUPT_HANDLERS_H
#define INTERRUPT_HANDLERS_H


#include <stdint.h>
#include "STM32L1xx.h"


#define EXTI_PR_CLEAR(n) ((uint32_t) (0x1 << (n)))
#define EXTI_PR (EXTI->PR)

/* Definition for pins when used in ODR masking. */
#define ODR_Pin(n) ((uint16_t) (0x1 << (n)))


/* Toggles a bitfield using BSRR.
       - Inputs:
           - GPIO_TypeDef gpio : The GPIO being considered.
           - uint16_t bitfield : Bitfield where 1 bits are toggles. */
void toggle_GPIO_bitfield(GPIO_TypeDef gpio, uint16_t bitfield);


/* User push button interrupt handler.
       - Toggles PC8 (an LED).
       - Sets second counter to count down. */
void EXTI0_IRQHandler(void);


/* Virtual switch interrupt handler. 
       - Toggles PC9 (an LED).
       - Sets second counter to count up. */
void EXTI1_IRQHandler(void);


#endif
