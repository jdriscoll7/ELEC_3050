/* - File: keypad_driver.h 

       - Description
           - Header file for keypad driver.
             
       - Author: Joe Driscoll 
*/


#ifndef KEYPAD_DRIVER_H
#define KEYPAD_DRIVER_H


#include <stdint.h>
#include <stdbool.h>
#include "STM32L1xx.h"
#include "pin_definitions.h"


/* Define the GPIO that the keypad is on. */
#define KEYPAD_GPIO  GPIOB
#define KEYPAD_RCC   GPIOB_RCC


#define KEYPAD_NUM_COLUMNS  4
#define KEYPAD_NUM_ROWS     4


#define ROW_BITFIELD ((uint16_t) (0x0F))
#define COL_BITFIELD ((uint16_t) (0xF0))


#define ROW_OFFSET 0
#define COL_OFFSET 4


/* Interconnect-dependent definitions. */
#define KEYPAD_ROW_INPUT_DATA   (KEYPAD_GPIO->IDR & ROW_BITFIELD)
#define KEYPAD_COL_INPUT_DATA   (KEYPAD_GPIO->IDR & COL_BITFIELD)
#define KEYPAD_INPUT_DATA       (KEYPAD_COL_INPUT_DATA | KEYPAD_ROW_INPUT_DATA)


/* Pull-up/pull-down definitions. */
#define KEYPAD_PULLUP_SET (0x0055)
#define KEYPAD_PULLUP_RST (~(0x00AA))


/* Columns are GPIO inputs. */
#define KEYPAD_ROW_MODER_SET    0x00
#define KEYPAD_ROW_MODER_CLR    ~(0x000000FF)


/* Rows are GPIO outputs. */
#define KEYPAD_COL_MODER_SET    (0x55 << (2*4))
#define KEYPAD_COL_MODER_CLR    ~(0x000000FF << (2*4))


/* Interrupt handler for the keypad device. */
void EXTI0_IRQHandler(void);


/* Lookup table for keypad. */
static const uint16_t keypad_decode_table[KEYPAD_NUM_ROWS][KEYPAD_NUM_COLUMNS] = {{0x1, 0x2, 0x3, 0xA},
                                                                                  {0x4, 0x5, 0x6, 0xB},
                                                                                  {0x7, 0x8, 0x9, 0xC},
                                                                                  {0xF, 0x0, 0xE, 0xD}};

                                                                                  
/* Internal variables that stores the key value and if a key was recently pressed. */
static bool key_pressed_flag = false;
static uint16_t key_pressed;


/* External interface - allows external programs to read key and check/reset key pressed flag. */
bool check_key_pressed(void);
uint16_t get_key_pressed(void);
void clear_key_pressed_flag(void);


/* Helper function for writing a value to a GPIO's ODR using the BSRR. */
static void keypad_write_to_odr(uint16_t value, uint16_t bitmask);


/* Reads the key pressed on the keypad and returns the number it represents. */
static uint16_t read_keypress(void);


/* Decode row-col pair to know what key was pressed. */
static uint16_t decode_row_col(uint16_t row, uint16_t col);


/* Keypad setup. */
void setup_keypad(void);


#endif
