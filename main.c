#include <stdint.h>
#include "STM32L1xx.h"


/* Definitions for switch_1 and switch_2 input data. */
#define SWITCH_1 ((GPIOA->IDR & 0x02) >> 1)
#define SWITCH_2 ((GPIOA->IDR & 0x04) >> 2)


/* Helper macro for mod function. */
#define MOD(a, b) (((a) + (b)) % (b))


/* Global variable for count. */
int8_t g_count = 0;


/* Hard-coded to setup specific pins. May be changed in future to allow parameters. */
void setup_pins()
{
    /* Setup input pins. */
    
    /* Enable GPIOA clock and set modes of PA1 and PA2 to input. */
    RCC->AHBENR |= 0x01;
    GPIOA->MODER &= ~(0x0000003C);

    /* Setup output pins. */
    
    /* Enable GPIOC clock and set modes of PC[3:0] to output ("01" repeated 4 times on lower bits of MODER). */
    RCC->AHBENR |= 0x04;
    GPIOC->MODER &= ~(0x000000AA);
    GPIOC->MODER |= 0x55;
    
    /* Reset PC[3:0] to ensure count of 0 on startup. */
    GPIOC->BSRR |= (0xF << 16);
}


/* Delays for 5 seconds by doing meaningless adds. */
void delay()
{
    uint32_t count = 0;
    
    /* Do 160 thousand adds (based on trial and error). */
    while (count < 160000)
    {
        count++;
    }       
}


/* Counts up for direction == 0 and down for direction == 1. */
uint8_t counting(uint8_t direction)
{
    /* Count up or down respectively. */
    if (direction == 0)
    {
        g_count = MOD(g_count + 1, 10);
    }
    else
    {
        g_count = MOD(g_count - 1, 10);
    }
    
    /* Write count to pins. */
    
    /* Set "on" bits and set "off" bits respectively. This assumes that 
    upper 4 bits of g_count are always 0 (which should be the case). This
    should be enforced by the if-else statement above.*/
    GPIOC->BSRR = (g_count & 0xF) | ((g_count ^ 0xF) << 16); 
    
    return g_count;
}


int main()
{
    setup_pins();
    
    while (1)
    {   
        /* Make sure switch is on. */
        while (SWITCH_1 == 1)
        {
            /* Delay and count. */
            delay();
            counting(SWITCH_2);
        }
    }
}
