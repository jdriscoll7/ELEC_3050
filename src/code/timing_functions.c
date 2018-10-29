/* - File: timing_functions.c 

       - Description
           - Provides timing functionality. Only in a separate file in
             anticipation for using the clock in later projects.
             
       - Author: Joe Driscoll 
*/


#include "timing_functions.h"
#include <stdlib.h>    


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
    TIM11->SR &= ~0x7;
}


/* Clear timer global variables and reset . */
void clear_timer(TIM_TypeDef *timer)
{       
    /* Reset timer's count register. */
    timer->CNT &= TIMER_CLEAR;
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


/* Initialize timer 10. */
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


/* Initialize timer 11. */
void setup_TIM11(void)
{
    /* Enable TIM11 clock on RCC. */
    RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;
    
    /* Enable TIM11 interrupt source in NVIC. */
    NVIC_EnableIRQ(TIM11_IRQn);
    
    /* Configure timer to default settings. */
    configure_timer(TIM11, TIM11_DEFAULT_PRESCALE, TIM11_DEFAULT_AUTO_RELOAD);
    
    /* Reset all values */
    TIM11->CCMR1 &= 0x0;
    
    /* Edit capture/compare select to input mode. */
    TIM11->CCMR1 |= 0x01;
    
    /* Make TIM11 generate interrupts. */
    TIM11->DIER &= 0x0;
    TIM11->DIER |= TIM_DIER_CC1IE;
    
    /* Enable capture/compare register - defaults to rising edge. */
    TIM11->CCER |= 0x1;
    
    /* Timer initially off. */
    disable_timer(TIM11);
}


/* TIM10 interrupt handler. */
void TIM10_IRQHandler(void)
{
    /* This interrupt handler shouldn't be called! (ever) */
    while(1);
}

