#include "setup.h"


/* Helper macro for mod function. */
#define MOD(a, b) ((((a) % (b)) < 0) ? (((a) % (b)) + (b)) : ((a) % (b)))


/* Switch definitions. */

/* Commented out for change in lab 4 specification. (interrupt driven) */
/*
#define SWITCH_1 (PA1_IDR)
#define SWITCH_2 (PA2_IDR)
*/


/* Global variable for count. */
int8_t g_count = 0;
int8_t g_count2 = 0;


/* Counts up for direction == 0 and down for direction == 1. */
uint8_t counting(uint8_t direction)
{
    /* First count (PC[3:0]) always counts up. */
    g_count = MOD(g_count + 1, 10);
    
    /* Only count when g_count is even. This caused second counter period to be
       double period of first counter (2 * 0.5s = 1s). */
    if ((g_count & 0x1) != 0)
    {
        /* Count up or down respectively. */
        if (direction == 0)
        {
            g_count2 = MOD(g_count2 + 1, 10);
        }
        else
        {
            g_count2 = MOD(g_count2 - 1, 10);
        }    
    }
    
    
    /* Write count to pins. */
    
    /* Set "on" bits and set "off" bits respectively. */
    uint32_t count_bitfield = (g_count & 0xF) | ((g_count ^ 0xF) << 16);
    uint32_t count2_bitfield = ((g_count2 & 0xF) << 4) | ((g_count2 ^ 0xF) << (16 + 4));
    
    /* Write counts at same time. */
    GPIOC->BSRR = count_bitfield | count2_bitfield;
    
    return g_count;
}


int main()
{
    setup_pins();
    setup_interrupts();

    while (1)
    {   
        /* Delay and count. */
        delay();
        counting(get_count_direction());
    }
    
}
