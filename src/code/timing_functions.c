/* - File: timing_functions.c 

       - Description
           - Provides timing functionality. Only in a separate file in
             anticipation for using the clock in later projects.
             
       - Author: Joe Driscoll 
*/

#include <stdint.h>


/* Delays for x seconds by doing meaningless adds. */
void delay(double seconds)
{
    uint32_t count = 0;
    uint32_t range = 262000 * 2 * seconds; 
    
    /* Do 160 thousand adds (based on trial and error). */
    while (count < range)
    {
        count++;
    }       
}
