/* - Name: interrupt_handlers.c 

       - Description
           - Provides the implementation to the interrupt handlers and
             some helper functions used by those handlers.
             
       - Author: Joe Driscoll
*/

#include "interrupt_handlers.h"
#include "keypad_driver.h"


/* Provides read access to count_direction from external files. */
uint8_t get_count_direction(void)
{
    return count_direction;
}


/* Toggles a bitfield using BSRR.
       - Inputs:
           - GPIO_TypeDef gpio : The GPIO being considered.
           - uint16_t bitfield : Bitfield where 1 bits are toggled. */
void toggle_GPIO_bitfield(GPIO_TypeDef *gpio, uint16_t bitfield)
{
    uint32_t bsrr_bitfield = 0;
    
    /* Set zeros to ones. */
    bsrr_bitfield |= ~(gpio->ODR) & bitfield;
       
    /* Set ones to zeros. */
    bsrr_bitfield |= ((gpio->ODR & bitfield) << 16);
           
    /* Write bsrr bitfield to bsrr of gpio input. */
    gpio->BSRR |= bsrr_bitfield;
}
