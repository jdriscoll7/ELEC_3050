/* - File: main.c

       - Description
           - Coordinates functionality in other files to meet specifications
             for current lab.
             
       - Author: Joe Driscoll 
*/

#include "setup.h"


/* Helper macro for mod function. */
#define MOD(a, b) ((((a) % (b)) < 0) ? (((a) % (b)) + (b)) : ((a) % (b)))


/* Helper macro for max function. */
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


/* Number of times cycles until count shows (after keypad press). */
#define KEYPAD_CYCLE_COUNT 5


/* Global variable for count. */
int8_t g_count = 0;
int8_t g_count2 = 0;


/* Counts up for direction == 0 and down for direction == 1. */
uint8_t counting(uint8_t direction)
{
    /* First count (PC[3:0]) always counts up. */
    g_count = MOD(g_count + 1, 10);
    
    return g_count;
}


int main()
{
    setup_pins();
    setup_interrupts();
    setup_keypad();

    /* Count to allow switching between keypad digit display and count display. */
    int8_t countdown_timer = 0;
    
    while (1)
    {   
        /* Delay and count. */
        delay(1);
        
        counting(g_count);
        
        /* Detect if keypad has been activated recently. */
        if (check_key_pressed() == true)
        {
            clear_key_pressed_flag();
            countdown_timer = KEYPAD_CYCLE_COUNT - 1;
        }
        
        /* If countdown timer is 0, then display count. If it isn't zero, 
           then it should be displaying a keypad character.*/
        if (countdown_timer == 0)
        {
            /* Write g_count to LED's. */
            write_to_odr(GPIOC, g_count, 0, 0x0F);
            
        }
        else
        {
            /* Write keypad button to LED's. */
            write_to_odr(GPIOC, get_key_pressed(), 0, 0x0F);
            
            /* Decrement countdown timer. */
            countdown_timer--;
        }
    }
}
