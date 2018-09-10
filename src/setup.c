#include "setup.h"


/* A large function that just sets up a few different pins for basic operation. */
void setup_pins()
{
    /* Setup input pins. */
    
    /* Enable GPIOA clock and set modes of PA0 and PA1 to input. */
    RCC->AHBENR |= GPIOA_RCC_EN;
    GPIOA->MODER &= ~(P0_MODE_INPUT | P1_MODE_INPUT);

    /* Setup output pins. */
    
    /* Enable GPIOC clock and set modes of PC[7:0] to output ("01" repeated 8 times on lower bits of MODER). */
    RCC->AHBENR |= GPIOC_RCC_EN;
    GPIOC->MODER &= ~(0x0000AAAA);
    GPIOC->MODER |= 0x5555;
    
    /* Reset PC[7:0] to ensure count of 0 on startup. */
    GPIOC->BSRR |= (0x00FF << 16);
}


/* Sets up PA0 and PA1 as interrupt sources that trigger EXTI0 and EXTI1 interrupt handlers respectively. */
void setup_interrupts()
{
    /* Setup interrupt source via SYSCFG. */
    SYSCFG_EXTICR1 = (SYSCFG_EXTICR1 & ~EXTICRn_PA(0)) | EXTICRn_PA_EN(0); /* PA0. */
    SYSCFG_EXTICR1 = (SYSCFG_EXTICR1 & ~EXTICRn_PA(1)) | EXTICRn_PA_EN(1); /* PA1. */

	/* Setup falling edge trigger for PA0 and PA1. */
    
    /* Unmask EXTI0 and EXTI1 interrupt using EXTI module. */
    
    /* Enable interrupt 0 and 1 in NVIC. */
    NVIC_EnableIRQ(EXTI0_IRQn);    
    NVIC_EnableIRQ(EXTI1_IRQn);
    
    /* Enable CPU interrupts. */
    enable_irq();
    
    
}
