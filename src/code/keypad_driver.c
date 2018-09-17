#include "keypad_driver.h"
#include "stdlib.h"


/* Function for creating a keypad interface. */
keypad_interface create_keypad_interface(GPIO_TypeDef gpio, uint16_t r_bitfield, uint16_t c_bitfield)
{
    keypad_interface new_keypad = malloc(sizeof(keypad_interface));
    
    new_keypad->gpio = gpio;
    new_keypad->row_bitfield = r_bitfield;
    new_keypad->col_bitfield = c_bitfield;
    
    return new_keypad;
    
}


/* Helper function for writing a value to a GPIO's ODR using the BSRR. */
static void write_to_odr(GPIO_TypeDef gpio, uint16_t value, uint16_t shift, uint16_t bitmask)
{
     gpio->BSRR |= ((value & bitmask) << shift) | ((value ^ bitmask) << (16 + shift));
}


/* Reads the key pressed on the keypad and returns the number it represents. */
uint16_t read_keypress(void)
{
    /* Drive all columns low and read rows. (row number will be a 0) */
    
    /* Drive all rows low and read columns. (column number will be a 0) */
    
    /* Decode the row and column number to return output. */
    
}


/* Decode row-col pair to know what key was pressed. 
       - Note: Does not work with pound or asterisk keys. */
uint16_t decode_row_col(uint16_t row, uint16_t col)
{   
    /* Is the key a letter? */
    if (col == 4)
    {
        return 0xA + (row - 1);
    }
    else
    {
        return col + 3 * (row - 1);
    }    
}
