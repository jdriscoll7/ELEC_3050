#include "interrupt_handlers.h"

/* User push button interrupt handler.
       - Toggles PC8 (an LED).
       - Sets second counter to count down. */
void EXTI0_IRQHandler(void)
{

    /* Clear pending interrupt signal. */
    CLEAR_INTERRUPT(0);
}


/* Virtual switch interrupt handler. 
       - Toggles PC9 (an LED).
       - Sets second counter to count up. */
void EXTI1_IRQHandler(void)
{
    /* Clear pening interrupt signal. */
    CLEAR_INTERRUPT(1);
}
