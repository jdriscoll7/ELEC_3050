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


#define TIMER_CLEAR         ((uint16_t) 0x0)


#define TIMER_ON_OR_OFF     (TIM10->CR1 & TIM_CR1_CEN)


/* Standard number of timers that can have their own function array. */
#define N_TIMERS 12


/* Function pointer and pointer to function pointer types. */
typedef void (*function_ptr)(void);
typedef function_ptr *function_ptr_ptr;


/* Variable for timer values. */
static uint8_t time_ones   = 0;
static uint8_t time_tenths = 0;


/* Clears timer interrupt. */
void clear_TIM10_interrupt(void);
void clear_TIM11_interrupt(void);


/* Array of function pointers to make interrupt handler flexible. */
static uint16_t function_count;
static function_ptr_ptr timer_function_array;
void set_timer_functions(TIM_TypeDef *timer, function_ptr new_functions, uint16_t size);


/* Decode timer number. */
uint16_t decode_timer_number(TIM_TypeDef *timer);

/* Function for getting time. */
uint16_t get_current_time(void);


/* Increment timer - returns next time. */
uint16_t increment_timer(void);


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


/* Delays for x seconds by doing meaningless adds. */
void delay(double seconds);


/* TIM10 interrupt handler. */
void TIM10_IRQHandler(void);


#endif
