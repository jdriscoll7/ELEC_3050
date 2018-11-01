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


/* Default 1 ms period. */
#define CLOCK_FREQ          16000000
#define DEFAULT_PERIOD      0.02
#define DEFAULT_PRESCALE    ((uint16_t) 4)
#define DEFAULT_AUTO_RELOAD ((uint16_t) 63999)


#define TIM11_DEFAULT_PERIOD      0.01
#define TIM11_DEFAULT_PRESCALE    ((uint16_t) 24)
#define TIM11_DEFAULT_AUTO_RELOAD ((uint16_t) 6399)


#define TIMER_CLEAR         ((uint16_t) 0x0)


#define TIMER_ON_OR_OFF     (TIM10->CR1 & TIM_CR1_CEN)


/* Standard number of timers that can have their own function array. */
#define N_TIMERS 12


/* Clears timer interrupt. */
void clear_TIM10_interrupt(void);
void clear_TIM11_interrupt(void);


/* Clear timer count. */
void clear_timer(TIM_TypeDef *timer);


/* Configure timer settings. */
void configure_timer(TIM_TypeDef *timer, uint16_t prescale, uint16_t auto_reload);


/* Set pwm parameters of timer. */
void set_timer_pwm_parameters(TIM_TypeDef *timer, uint16_t ccr, uint16_t arr);


/* Enable counting on timer. */
void enable_timer(TIM_TypeDef *timer);


/* Disable counting on timer. */
void disable_TIM10(TIM_TypeDef *timer);


/* Toggle TIM10 on/off. */
void toggle_enable_TIM10(void);


/* Initialize timers. */
void setup_TIM10(void);
void setup_TIM11(void);


/* TIM10 interrupt handler. */
void TIM10_IRQHandler(void);


#endif
