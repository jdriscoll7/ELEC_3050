/* - File: bcd_timer.c
       - Description
           - Implements bcd timer interface.
             
       - Author: Joe Driscoll 
*/


#include "bcd_timer.h"
#include "setup.h"
#include "stdint.h"


/* Timer data. */
static uint8_t ones_place;
static uint8_t tenths_place;


/* Increments timer and returns current timer. */
uint8_t increment_timer(void)
{
    /* Increment counter. */
    tenths_place = MOD(tenths_place + 1, 10);
    
    /* If tenths place just rolled over to zero, increment ones place. */
    if (tenths_place == 0)
    {
        ones_place = MOD(ones_place + 1, 10);
    }
    
    /* Return new BCD value (wrangle into 8 bits). */
    return (((uint8_t) (ones_place << 4)) | tenths_place);
}
