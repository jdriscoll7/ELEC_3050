#ifndef INTERRUPT_HANDLERS_H
#define INTERRUPT_HANDLERS_H


#include <stdint.h>
#include "STM32L1xx.h"


/* User push button interrupt handler.
       - Toggles PC8 (an LED).
       - Sets second counter to count down. */
void EXTI0_IRQHandler(void);


/* Virtual switch interrupt handler. 
       - Toggles PC9 (an LED).
       - Sets second counter to count up. */
void EXTI1_IRQHandler(void);


#endif
