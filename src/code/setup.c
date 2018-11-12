/* - File: setup.c 

       - Description
           - Provides implementation of functions that make 
             setting up essential parts of a project up, including pin 
             and interrupt functions and setup, simpler.
             
       - Author: Joe Driscoll 
*/


#include "setup.h"


/* Function for writing to a GPIO ODR. */
void write_to_odr(GPIO_TypeDef *gpio, uint16_t value, uint16_t shift, uint16_t bitmask)
{
     uint32_t masked_value = value & bitmask;
     gpio->BSRR |= (masked_value << shift) | ((masked_value ^ bitmask) << (16 + shift));
}


/* A large function that just sets up a few different pins for basic operation. 
        
        This can be seen as a clock setup function that also configures a bunch
        of LEDs (previously for labs, now for debugging if needed).
        
        Current setup:
            - Turn on HSI clock.
            - Configure PA0 and PA1 as inputs.
            - Configure PC[7:0] as outputs.
            - Configure PC[9:8] as outputs.
            - Configure PA6 as output (for PWM).
            - Configure PA7 as input capture.
            - Configure PA0 as analog input (ADC).
*/
void setup_pins()
{
    /* Turn on HSI clock. */
    RCC->CR |= RCC_CR_HSION;
    while ((RCC->CR & RCC_CR_HSIRDY) == 0);
    RCC->CFGR |= RCC_CFGR_SW_HSI;
    
    /* Setup input pins. */
    
    /* Enable GPIOA clock and set modes of PA0 and PA1 to input. */
    RCC->AHBENR |= GPIOA_RCC_EN;
    GPIOA->MODER &= ~(P0_MODE_INPUT | P1_MODE_INPUT);

    /* Setup output pins. */
    
    /* Enable GPIOC clock and set modes of PC[7:0] to output ("01" repeated 8 times on lower bits of MODER). */
    RCC_AHBENR |= GPIOC_RCC_EN;
    GPIOC_MODER &= PC70_DOUT_CLR; /* Clear relevant mode bits. */
    GPIOC_MODER |= PC70_DOUT_SET; /* Set relevant mode bits. */
    
    /* Reset PC[7:0] to ensure count of 0 on startup. */
    GPIOC->BSRR |= (0x00FF << 16);
    
    /* Enable PC8 and PC9 as digital output. (LEDs) */
    GPIOC_MODER &= PC98_DOUT_CLR; /* Clear relevant mode bits. */
    GPIOC_MODER |= PC98_DOUT_SET; /* Set relevant mode bits. */
       
    /* Set PA6 as alternate function (PWM). */
    GPIOA_MODER &= PWM_MODE_CLR;
    GPIOA_MODER |= PWM_MODE_SET;
    GPIOA->AFR[0] &= ~0x0F000000; //clear AFRL6
    GPIOA->AFR[0] |= 0x03000000;  //PA6 = AF3
    
    /* Set PA7 as alternate function (input capture). */
    GPIOA_MODER &= ICM_MODE_CLR;
    GPIOA_MODER |= ICM_MODE_SET;
    GPIOA->AFR[0] &= ~0xF0000000; //clear AFRL7
    GPIOA->AFR[0] |= 0x30000000;  //PA7 = AF3
    
    /* Set PA0 as ADC (analog) input. */
    GPIOA_MODER |= ADC_MODE;
}


/* Sets up PA1 as interrupt source that triggers EXTI1 interrupt handler. */
void setup_interrupts()
{
    /* Setup interrupt source via SYSCFG. */
    SYSCFG_EXTICR1 = (SYSCFG_EXTICR1 & ~EXTICRn_PA(1)) | EXTICRn_PA_EN(1);

    /* Setup falling edge trigger for PA1. */
    EXTI_FTSR = (EXTI_FTSR & ~EXTI_EDGE_EN(1)) | EXTI_EDGE_EN(1);
    
    /* Unmask EXTI1 interrupt using EXTI module. */
    EXTI_IMR = (EXTI_IMR & ~EXTI1_IMR_MASK) | EXTI1_IMR_MASK;

    /* Enable EXTI interrupt 1 in NVIC. */
    NVIC_EnableIRQ(EXTI1_IRQn);
    
    /* Enable CPU interrupts. */
    __enable_irq();
}

