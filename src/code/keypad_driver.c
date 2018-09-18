#include "keypad_driver.h"
#include "stdlib.h"


/* Helper function for writing a value to a GPIO's ODR using the BSRR. */
static void keypad_write_to_odr(uint16_t value, uint16_t bitmask)
{
     KEYPAD_GPIO->BSRR |= (value & bitmask) | (((value & bitmask) ^ bitmask) << 16);
}


/* Reads the key pressed on the keypad and returns the number it represents. */
uint16_t read_keypress(void)
{
    /* Iterate columns and read every row per interation. */
    for (uint16_t column = 0; column < KEYPAD_NUM_COLUMNS; column++)
    {
        /* Drive column low. */
        keypad_write_to_odr(~(0x1 << column), 0xF);
        
        uint16_t shifted_row_input_data = (KEYPAD_ROW_INPUT_DATA >> ROW_OFFSET);
         
        /* Are any rows driven low? */
        if (shifted_row_input_data != 0xF)
        {
            /* 4-bit value with a zero in current column and ones in other (three) columns. */
            uint16_t row_data = (~(shifted_row_input_data) & 0xF) / 2;
            
            uint16_t row = 0;
            
            /* Find index of row that is a zero. */
            while (row_data > 0)
            {
                row_data = (row_data >> 1);
                row++;
            }
            
            /* Reset all column values to low to allow interrupt retriggering. */
            keypad_write_to_odr(0x0, 0xF);
             
            /* Return correct decoding. */
            return decode_row_col(row + 1, column + 1);
        }
    }
    
    /* If function reaches here, then there was an error. Always output F to detect error on testing. */
    return 0xF;
}


/* Decode row-col pair to know what key was pressed. 
       - Note: Does not work with pound or asterisk keys. */
uint16_t decode_row_col(uint16_t row, uint16_t col)
{   
    uint16_t lookuptable
     
    /* Is the key a letter? */
    if (col == 4)
    {
        return 0xA + (row - 1);
    }
    else if (row == 4 && (col == 3 || col == 1))
    {
        /* Always return 0xF for special characters. */
        return 0xF;
    }
    else
    {
        return MOD(col + 3 * (row - 1), 10);
    }    
}



/* Interrupt handler for keypad interrupt. */
void EXTI1_IRQHandler(void)
{
    /* Set pressed flag and the key pressed. */
    key_pressed = read_keypress();
    key_pressed_flag = true;
    
    /* Clear EXTI pending register for interrupt source 1 (PA1). */
    EXTI_PR |= EXTI_PR_CLEAR(1);

    /* Clear pending interrupt signal. */
    NVIC_ClearPendingIRQ(EXTI1_IRQn);
}


/* Check for key pressed. */
bool check_key_pressed(void)
{
    return key_pressed_flag;
}


/* Return the key pressed. */
uint16_t get_key_pressed(void)
{
    return key_pressed;
}


/* Clear key_pressed_flag. */
void clear_key_pressed_flag(void)
{
    key_pressed_flag = false;
}
