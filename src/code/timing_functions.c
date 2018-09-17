/* - File: timing_functions.c 

       - Description
           - Provides timing functionality. Only in a separate file in
             anticipation for using the clock in later projects.
             
       - Author: Joe Driscoll 
*/

#include <stdint.h>


/* Delays for 0.5 seconds by doing meaningless adds. */
void delay()
{
    uint32_t count = 0;
    
    /* Do 160 thousand adds (based on trial and error). */
    while (count < 160000)
    {
        count++;
    }       
}
