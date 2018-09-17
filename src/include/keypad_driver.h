/* - File: keypad_driver.h 

       - Description
           - A sort of device driver for the keypad
             used in the projects.
             
       - Author: Joe Driscoll 
*/


#ifndef KEYPAD_DRIVER_H
#define KEYPAD_DRIVER_H


#include <stdint.h>
#include "STM32L1xx.h"
#include "pin_definitions.h"


/* Define the GPIO that the keypad is on. */
#define KEYPAD_GPIO  GPIOB
#define KEYPAD_RCC   GPIOB_RCC


#define KEYPAD_NUM_COLUMNS  4
#define KEYPAD_NUM_ROWS     4


#define ROW_BITFIELD ((uint16_t) (0xF0))
#define COL_BITFIELD ((uint16_t) (0x0F))


#define ROW_OFFSET 4
#define COL_OFFSET 0


/* Columns are GPIO inputs. */
#define KEYPAD_COL_MODER_SET    0x00
#define KEYPAD_COL_MODER_CLR    0xFF

/* Rows are GPIO outputs. */
#define KEYPAD_ROW_MODER_SET    (0x55 << 4)
#define KEYPAD_ROW_MODER_CLR    ~(0x000000AA << 4)


/* Interconnect-dependent definitions. */
#define KEYPAD_ROW_INPUT_DATA   (KEYPAD_GPIO->IDR & ROW_BITFIELD)
#define KEYPAD_COL_INPUT_DATA   (KEYPAD_GPIO->IDR & COL_BITFIELD)
#define KEYPAD_INPUT_DATA       (KEYPAD_COL_INPUT_DATA | KEYPAD_ROW_INPUT_DATA)


/* Interrupt handler for the keypad device. */
extern void EXTI0_IRQHandler(void);


/* Helper function for writing a value to a GPIO's ODR using the BSRR. */
static void keypad_write_to_odr(uint16_t value, uint16_t shift, uint16_t bitmask);


/* Reads the key pressed on the keypad and returns the number it represents. */
static uint16_t read_keypress(void);


/* Decode row-col pair to know what key was pressed. */
static uint16_t decode_row_col(uint16_t row, uint16_t col);


#endif
