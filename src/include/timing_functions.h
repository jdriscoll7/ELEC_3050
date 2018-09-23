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


#define TIMER_ON_OR_OFF     (TIM10->CR1 & TIM_CR1_CEN)


/* Global variable for timer values. */
static int8_t g_time_ones   = 0;
static int8_t g_time_tenths = 0;


/* Clear timer global variables. */
void clear_timer_globals(void);


/* Configure timer settings. */
void configure_timer(TIM_TypeDef *timer, uint16_t prescale, uint16_t auto_reload);


/* Enable counting on timer. */
void enable_TIM10(void);


/* Disable counting on timer. */
void disable_TIM10(void);


/* Toggle TIM10 on/off. */
void toggle_enable_TIM10(void);


/* Initialize timer. */
void setup_TIM10(void);


/* Delays for x seconds by doing meaningless adds. */
void delay(double seconds);


/* TIM10 interrupt handler. */
void TIM10_IRQHandler(void);


#endif
