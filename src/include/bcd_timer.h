/* - File: bcd_timer.h
       - Description
           - Provides interface and definitions for bcd timer.
             
       - Author: Joe Driscoll 
*/


#ifndef BCD_TIMER_H
#define BCD_TIMER_H


#include "stdint.h"


/* Increments timer - returns BCD time as 8-bit number (upper four bits as ones place, lower four as tenths place). */
uint8_t increment_timer(void);


/* Turns timer on and off. */
void bcd_timer_off(void);
void bcd_timer_on(void);
uint8_t get_timer_status(void);
void clear_bcd(void);

#endif
