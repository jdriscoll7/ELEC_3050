#include "interrupt_handlers.h"


/* Provides read access to count_direction from external files. */
uint8_t get_count_direction(void)
{
    return count_direction;
}


/* Toggles a bitfield using BSRR.
       - Inputs:
           - GPIO_TypeDef gpio : The GPIO being considered.
           - uint16_t bitfield : Bitfield where 1 bits are toggles. */
void toggle_GPIO_bitfield(GPIO_TypeDef *gpio, uint16_t bitfield)
{
    uint32_t bsrr_bitfield = 0;
    
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
    uint32_t count = 0;
    
    /* Do 160 thousand adds (based on trial and error). */
    while (count < 160000)
    {
        count++;
    }   
    
    /* Toggle PC8 LED. */
    toggle_GPIO_bitfield(GPIOC, ODR_PIN(8));
       
    /* Set count direction to down. */
    count_direction = COUNT_DOWN;
    
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
    toggle_GPIO_bitfield(GPIOC, ODR_PIN(9));
       
    /* Set count direction to up. */
    count_direction = COUNT_UP;
    
    /* Clear EXTI pending register for interrupt source 1 (PA1). */
    EXTI_PR |= EXTI_PR_CLEAR(1);
    
    /* Clear pending interrupt signal. */
    NVIC_ClearPendingIRQ(EXTI1_IRQn);
}
