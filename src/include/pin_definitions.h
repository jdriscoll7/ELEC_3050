/* - File: pin_definitions.h 

       - Description
           - Contains all pin definitions shared by files, like RCC register locations
             and GPIO locations.
             
       - Author: Joe Driscoll 
*/


#ifndef PIN_DEFINITIONS_H
#define PIN_DEFINITIONS_H


/* GPIO clock enable definitions. */
#define RCC_AHBENR   (RCC->AHBENR)
#define GPIOA_RCC_EN 0x01
#define GPIOB_RCC_EN 0x02
#define GPIOC_RCC_EN 0x04


/* Interrupt setup definitions. */
#define SYSCFG_EXTICR1   (SYSCFG->EXTICR[0])
#define EXTI_IMR         (EXTI->IMR)
#define EXTI_FTSR        (EXTI->FTSR)
#define EXTI_RTSR        (EXTI->RTSR)
#define EXTICRn_PA(x)    ((uint32_t) (0xF << (4*(x))))
#define EXTICRn_PA_EN(x) ((uint32_t) (0x0 << (4*(x))))
#define EXTI0_IMR_MASK   ((uint32_t) 0x01)
#define EXTI1_IMR_MASK   ((uint32_t) 0x02)
#define EXTI_EDGE_EN(n)  ((uint32_t) (0x01 << (n)))


#endif
