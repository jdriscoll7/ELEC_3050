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


#endif
