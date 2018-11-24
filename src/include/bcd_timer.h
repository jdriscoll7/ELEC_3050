/* - File: bcd_timer.h
       - Description
           - Provides interface and definitions for bcd timer.
             
       - Author: Joe Driscoll 
*/


#ifndef BCD_TIMER_H
#define BCD_TIMER_H


/* Timer type definitions (easier than managing global variable). */
typedef struct bcd_timer
{
    uint8_t ones_place;
    uint8_t tenths_place;
} bcd_timer_t;


/* Increments timer - returns BCD time as 8-bit number (upper four bits as ones place, lower four as tenths place). */
uint8_t increment_timer(void);


#endif
