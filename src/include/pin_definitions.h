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


/* Definitions for specific pin MODER modes. */
#define P0_MODE_INPUT 0x00000003
#define P1_MODE_INPUT 0x0000000C
#define P2_MODE_INPUT 0x00000030


/* Definitions for GPIOA input data registers. */
#define PA0_IDR ((uint16_t) (GPIOA->IDR & 0x01))
#define PA1_IDR ((uint16_t) (GPIOA->IDR & 0x02))
#define PA2_IDR ((uint16_t) (GPIOA->IDR & 0x04))


/* GPIOC ODR for reading LED states. */
#define PC8_ODR ((uint16_t) (GPIOC->ODR & 0x100))
#define PC9_ODR ((uint16_t) (GPIOC->ODR & 0x200))


#endif
