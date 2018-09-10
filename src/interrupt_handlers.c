#include "interrupt_handlers.h"


/* User push button interrupt handler.
       - Toggles PC8 (an LED).
       - Sets second counter to count down. */
void EXTI0_IRQHandler(void)
{

    /* Clear pending interrupt signal. */
    NVIC_ClearPendingIRQ(EXTI0_IRQn);
}


/* Virtual switch interrupt handler. 
       - Toggles PC9 (an LED).
       - Sets second counter to count up. */
void EXTI1_IRQHandler(void)
{
    /* Clear pending interrupt signal. */
    NVIC_ClearPendingIRQ(EXTI1_IRQn);
}
