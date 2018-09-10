#include <stdint.h>
#include "setup.h"


/* A large function that just sets up a few different pins for basic operation. */
void setup_pins()
{
    /* Setup input pins. */
    
    /* Enable GPIOA clock and set modes of PA1 and PA2 to input. */
    RCC->AHBENR |= GPIOA_RCC_EN;
    GPIOA->MODER &= ~(P1_MODE_INPUT | P2_MODE_INPUT);

    /* Setup output pins. */
    
    /* Enable GPIOC clock and set modes of PC[7:0] to output ("01" repeated 8 times on lower bits of MODER). */
    RCC->AHBENR |= GPIOC_RCC_EN;
    GPIOC->MODER &= ~(0x0000AAAA);
    GPIOC->MODER |= 0x5555;
    
    /* Reset PC[7:0] to ensure count of 0 on startup. */
    GPIOC->BSRR |= (0x00FF << 16);
}

void setup_interrupts()
{
    
}
