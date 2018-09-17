/* - File: setup.h 

       - Description
           - Provides definitions and function declarations that make 
             setting up essential parts of a project up, including pin and
             interrupt definitions and functions, easier.
             
       - Author: Joe Driscoll 
*/


#ifndef SETUP_H
#define SETUP_H


#include <stdint.h>
#include "STM32L1xx.h"
#include "timing_functions.h"
#include "interrupt_handlers.h"
#include "keypad_driver.h"
#include "pin_definitions.h"


/* GPIO definitions. */
#define PC70_DOUT_SET   (0x5555)            /* Bits to set for PC[7:0] MODER (output). */
#define PC70_DOUT_CLR   (~0x0000AAAA)       /* Bits to clear for PC[7:0] MODER (output). */
#define PC98_DOUT_SET   (0x05 << (2*8))     /* Bits to set for PC[9:8] MODER (output). */
#define PC98_DOUT_CLR   (~(0x0A << (2*8)))  /* Bits to clear for PC[9:8] MODER (output). */


/* Define the GPIO that the keypad is on. */
#define KEYPAD_GPIO GPIOB


/* Function for writing to a GPIO ODR. */
void write_to_odr(GPIO_TypeDef gpio, uint16_t value, uint16_t shift, uint16_t bitmask);


/* Hard-coded to setup specific pins. May be changed in future to allow parameters. */
void setup_pins(void);


/* Sets up PA0 and PA1 as interrupts. */
void setup_interrupts(void);


/* Setup keypad interface. */
void setup_keypad_ports(void);


#endif
