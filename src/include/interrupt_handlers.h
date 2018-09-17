/* - File: interrupt_handlers.h 

       - Description
           - Provides various definitions and function declarations
             used in interrupt handling.
             
       - Author: Joe Driscoll 
*/


#ifndef INTERRUPT_HANDLERS_H
#define INTERRUPT_HANDLERS_H


#include <stdint.h>
#include "STM32L1xx.h"


/* Count up/down definitions for counter. */
#define COUNT_UP   ((uint16_t) 0x0)
#define COUNT_DOWN ((uint16_t) 0x1)


/* Variable used by main function that only interrupt handlers can access. */
static uint16_t count_direction;


/* Provides read access to count_direction from external files. */
uint8_t get_count_direction(void);


/* Toggles a bitfield using BSRR.*/
void toggle_GPIO_bitfield(GPIO_TypeDef *gpio, uint16_t bitfield);


/* User push button interrupt handler. */
void EXTI0_IRQHandler(void);


/* Virtual switch interrupt handler. */
void EXTI1_IRQHandler(void);


#endif
