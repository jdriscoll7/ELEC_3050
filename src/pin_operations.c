#include <stdint.h>
#include "pin_operations.h"


/* A large function that just sets up a few different pins for basic operation. */
void setup_pins()
{
    /* Setup input pins. */
    
    /* Enable GPIOA clock and set modes of PA1 and PA2 to input. */
    RCC->AHBENR |= 0x01;
    GPIOA->MODER &= ~(0x0000003C);

    /* Setup output pins. */
    
    /* Enable GPIOC clock and set modes of PC[7:0] to output ("01" repeated 8 times on lower bits of MODER). */
    RCC->AHBENR |= 0x04;
    GPIOC->MODER &= ~(0x0000AAAA);
    GPIOC->MODER |= 0x5555;
    
    /* Reset PC[3:0] to ensure count of 0 on startup. */
    GPIOC->BSRR |= (0xFFFF << 16);
}
