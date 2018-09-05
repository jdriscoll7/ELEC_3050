#include <stdint.h>
#include "STM32L1xx.h"
#include "setup.h"
#include "timing_functions.h"


/* Helper macro for mod function. */
#define MOD(a, b) ((((a) % (b)) < 0) ? (((a) % (b)) + (b)) : ((a) % (b)))


/* Switch definitions. */
#define SWITCH_1 (PA1_IDR)
#define SWITCH_2 (PA2_IDR)


/* Global variable for count. */
int8_t g_count = 0;
int8_t g_count2 = 0;


/* Counts up for direction == 0 and down for direction == 1. */
uint8_t counting(uint8_t direction)
{
    /* Count up or down respectively. */
    if (direction == 0)
    {
        g_count = MOD(g_count + 1, 10);
        g_count2 = MOD(g_count2 - 1, 10);
    }
    else
    {
        g_count = MOD(g_count - 1, 10);
        g_count2 = MOD(g_count2 + 1, 10);
    }
    
    /* Write count to pins. */
    
    /* Set "on" bits and set "off" bits respectively. (temp variables are wasteful but easier to understand)*/
    uint32_t count_bitfield = (g_count & 0xF) | ((g_count ^ 0xF) << 16);
    uint32_t count2_bitfield = ((g_count2 & 0xF) << 4) | ((g_count2 ^ 0xF) << (16 + 4));
    
    /* Write counts at same time. */
    GPIOC->BSRR = count_bitfield | count2_bitfield;
    
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
