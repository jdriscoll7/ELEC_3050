/* - File: timing_functions.c 

       - Description
           - Provides timing functionality. Only in a separate file in
             anticipation for using the clock in later projects.
             
       - Author: Joe Driscoll 
*/


#include "timing_functions.h"
#include <stdlib.h>    


/* Increment timer - returns next time. */
uint16_t increment_timer(void)
{
    /* Increment ones place if tenth's place rolls over. */
    if (time_tenths == 9)
    {
        time_ones = MOD(time_ones + 1, 10);
    }
    
    /* First count (PC[3:0]) is tenth of a second base. */
    time_tenths = MOD(time_tenths + 1, 10);
       
    return get_current_time();
}


/* Clears timer interrupt. */
void clear_TIM10_interrupt(void)
{
    NVIC_ClearPendingIRQ(TIM10_IRQn);
    TIM10->SR &= ~0x1;
}


/* Clears timer interrupt. */
void clear_TIM11_interrupt(void)
{
    NVIC_ClearPendingIRQ(TIM11_IRQn);
    TIM11->SR &= ~0x1;
}


/* Decode timer number. */
uint16_t decode_timer_number(TIM_TypeDef *timer)
{
    switch((uint32_t) timer)
    {    
        case ((uint32_t) TIM2):
            return 2;
        case ((uint32_t) TIM3):
            return 3;
        case ((uint32_t) TIM4):
            return 4;
        case ((uint32_t) TIM6):
            return 6;
        case ((uint32_t) TIM9):
            return 9;
        case ((uint32_t) TIM10):
            return 10;
        case ((uint32_t) TIM11):
            return 11;
    };
    
    return 0;
}


void set_timer_functions(TIM_TypeDef *timer, function_ptr new_functions, uint16_t size)
{
    uint16_t timer_number = decode_timer_number(timer);
    
    /* Free previous function array if it isn't empty. */
    if (function_count[timer_number] != 0)
    {
        free(timer_function_array[timer_number]);
    }
       
    /* Reserve memory for function pointers and make room for additional PR clear function. */
    function_count[timer_number] = size;
    timer_function_array[timer_number] = malloc(size*sizeof(function_ptr));
       
    /* Set array to the input and add the clear interrupt function at the end. */
    timer_function_array[timer_number][0] = new_functions;
}


/* Function for getting time. */
uint16_t get_current_time(void)
{
    return ((uint16_t) ((time_ones << 4) + time_tenths));
}


/* Clear timer global variables and reset . */
void clear_timer(void)
{
    /* Reset global variables holding count. */
    time_ones = 0;
    time_tenths = 0;
       
    /* Reset timer's count register. */
    TIM10_COUNT &= TIMER_CLEAR;

    /* Write value. */
    write_to_odr(GPIOC, get_current_time(), NO_SHIFT, 0xFF);
}


/* Disable counting on timer. */
void disable_timer(TIM_TypeDef *timer)
{
    timer->CR1 &= ~TIM_CR1_CEN;
}


/* Set pwm parameters of timer. */
void set_timer_pwm_parameters(TIM_TypeDef *timer, uint16_t ccr, uint16_t arr)
{
    timer->CCR1 |= ((uint32_t) ccr);
    timer->CCR1 &= ~((uint32_t) ~ccr);
    
    timer->ARR |= ((uint32_t) arr);
    timer->ARR &= ~((uint32_t) ~arr);
}


/* Enable counting on timer. */
void enable_timer(TIM_TypeDef *timer)
{
    timer->CR1 |= TIM_CR1_CEN;
}


/* Toggle TIM10 on/off. */
void toggle_enable_timer(TIM_TypeDef *timer)
{
    /* If on, turn off and vice versa. */
    if (TIMER_ON_OR_OFF != 0)
    {
        disable_timer(timer);
    }
    else
    {
        enable_timer(timer);
    }
}


/* Configure timer settings. */
void configure_timer(TIM_TypeDef *timer, uint16_t prescale, uint16_t auto_reload)
{
    timer->ARR = auto_reload;
    timer->PSC = prescale;
}


/* Initialize timer. */
void setup_TIM10(void)
{
    /* Enable TIM10 clock on RCC. */
    RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
    
    /* Enable TIM10 interrupt source in NVIC. */
    //NVIC_EnableIRQ(TIM10_IRQn);
    
    /* Make TIM10 generate interrupts. */
    //TIM10->DIER |= TIM_DIER_UIE;
    
    /* Configure timer to default settings. */
    configure_timer(TIM10, DEFAULT_PRESCALE, DEFAULT_AUTO_RELOAD);
    
    /* PWM mode 1 (active high). */
    TIM10->CCMR1 |= 0x60;
    
    /* Enable capture/compare register. */
    TIM10->CCER |= 0x1;
    
    /* Timer initially off. */
    disable_timer(TIM10);
}


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


/* TIM10 interrupt handler. */
void TIM10_IRQHandler(void)
{
    for (int function = 0; function < function_count[10]; function++)
    {
        timer_function_array[10][function]();
    }
    
    clear_TIM10_interrupt();
}


/* TIM11 interrupt handler. */
void TIM11_IRQHandler(void)
{
    for (int function = 0; function < function_count[11]; function++)
    {
        timer_function_array[11][function]();
    }
    
    clear_TIM11_interrupt();
}