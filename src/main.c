/* - File: main.c

       - Description
           - Coordinates functionality in other files to meet specifications
             for current lab.
             
       - Author: Joe Driscoll 
*/

#include "setup.h"


/* Helper macro for mod function. */
#define MOD(a, b) ((((a) % (b)) < 0) ? (((a) % (b)) + (b)) : ((a) % (b)))


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
    if ((g_count & 0x1) == 0)
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
    
    /* Write counts at same time - lots of casting for safety. */
       
    /* Combine counts. */
    uint16_t combined_counts = ((uint16_t) g_count) + (((uint16_t) g_count2) << 4);
           
    /* Write combined counts to GPIOC ODR, with the count being offset by 0 and writing to lower 8 bits (0xFF). */
    write_to_odr(GPIOC, combined_counts, 0, 0xFF);
    
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
