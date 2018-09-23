/* - File: timing_functions.c 

       - Description
           - Provides timing functionality. Only in a separate file in
             anticipation for using the clock in later projects.
             
       - Author: Joe Driscoll 
*/


#include "timing_functions.h"


/* Sets up clocks and interrupts for TIM10. */
static void enable_TIM10(void)
{
    /* Enable TIM10 clock on RCC. */
    RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
    
    /* Enable TIM10 interrupt source in NVIC. */
    NVIC_EnableIRQ(TIM10_IRQn);
    
    /* Make TIM10 generate interrupts. */
    TIM10->DIER |= TIM_DIER_UIE;
}


/* Disable counting on timer. */
void disable_TIM10(void)
{
    TIM10->CR1 &= ~TIM_CR1_CEN;
}


/* Configure timer settings. */
void configure_timer(TIM_TypeDef *timer, uint16_t prescale, uint16_t auto_reload)
{
    timer->ARR = auto_reload;
    timer->PSC = prescale;
}


/* Initialize timer. */
void setup_timer(void)
{
    /* Configure timer to default settings. */
    configure_timer(TIM10, DEFAULT_PRESCALE, DEFAULT_AUTO_RELOAD);
    
    /* Make timer begin counting. */
    TIM10->CR1 |= TIM_CR1_CEN;
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
    /* Clear all interrupt request pending registers. */
    NVIC_ClearPendingIRQ(TIM10_IRQn);
    TIM10->SR &= ~0x1;
}
