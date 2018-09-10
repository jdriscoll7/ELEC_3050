#include "interrupt_handlers.h"


/* Toggles a bitfield using BSRR.
       - Inputs:
           - GPIO_TypeDef gpio : The GPIO being considered.
           - uint16_t bitfield : Bitfield where 1 bits are toggles*/
void toggle_GPIO_bitfield(GPIO_TypeDef gpio, uint16_t bitfield)
{
    uint32_t bsrr_bitfield;
    
    /* Set zeros to ones. */
    bsrr_bitfield |= ~(gpio->ODR) & bitfield;
       
    /* Set ones to zeros. */
    bsrr_bitfield |= ((gpio->ODR & bitfield) << 16);
           
    /* Write bsrr bitfield to bsrr of gpio input. */
    gpio->BSRR |= bsrr_bitfield;
}


/* User push button interrupt handler.
       - Toggles PC8 (an LED).
       - Sets second counter to count down. */
void EXTI0_IRQHandler(void)
{
    /* Clear EXTI pending register for interrupt source 0 (PA0). */
    EXTI_PR |= EXTI_PR_CLEAR(0);

    /* Clear pending interrupt signal. */
    NVIC_ClearPendingIRQ(EXTI0_IRQn);
}


/* Virtual switch interrupt handler. 
       - Toggles PC9 (an LED).
       - Sets second counter to count up. */
void EXTI1_IRQHandler(void)
{
    /* Toggle PC9 LED. */
    
       
    /* Clear EXTI pending register for interrupt source 1 (PA1). */
    EXTI_PR |= EXTI_PR_CLEAR(1);
    
    /* Clear pending interrupt signal. */
    NVIC_ClearPendingIRQ(EXTI1_IRQn);
}
