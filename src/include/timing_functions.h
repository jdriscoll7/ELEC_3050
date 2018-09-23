/* - File: timing_functions.h 

       - Description
           - Contains timing functions, including timer interrupt handlers
             and setup.
             
       - Author: Joe Driscoll 
*/


#ifndef TIMING_FUNCTIONS_H
#define TIMING_FUNCTIONS_H


#include "setup.h"
#include <stdint.h>


#define CLOCK_FREQ          (0x1 << 24)
#define DEFAULT_PERIOD      0.1
#define DEFAULT_PRESCALE    ((uint16_t) 15)
#define DEFAULT_AUTO_RELOAD ((uint16_t) 99)


/* Enable interrupts for TIM10. */
static void enable_TIM10(void);


/* Configure timer settings. */
void configure_timer(TIM_TypeDef *timer, uint16_t prescale, uint16_t auto_reload);


/* Disable counting on timer. */
void disable_TIM10(void);


/* Initialize timer. */
void setup_timer(void);


/* Delays for x seconds by doing meaningless adds. */
void delay(double seconds);


/* TIM10 interrupt handler. */
void TIM10_IRQHandler(void);


#endif
