/* - File: main.c

       - Description
           - Coordinates functionality in other files to meet specifications
             for current lab.
             
       - Author: Joe Driscoll 
*/

#include "setup.h"


/* Number of times cycles until count shows (after keypad press). */
#define KEYPAD_CYCLE_COUNT 5

/* Define which keypad keys turn on and off timer. */
#define TIMER_ENABLE_KEY    0xF
#define TIMER_CLEAR_KEY     0xE


void increment_and_display(void)
{
    increment_timer();
       
    /* Write count, overlaying ones-count to upper four bits and tenths to lower four bits. */
    write_to_odr(GPIOC, get_current_time(), NO_SHIFT, 0xFF);
}


int main()
{
    setup_pins();
    setup_interrupts();
    setup_keypad();
    setup_TIM10();
    set_TIM10_functions({increment_and_display}, 1);
    
    while (1)
    {
        /* Detect if keypad has been activated recently. */
        if (check_key_pressed() == true)
        {
            /* Decode key and set the duty cycle. */
            uint16_t key_pressed = get_key_pressed();
            set_duty_cycle(KEY_TO_DUTY_CYCLE(key_pressed));
            
            /* Display duty cycle on LEDs. */
            write_to_odr(GPIOC, key_pressed, NO_SHIFT, 0xF);

            clear_key_pressed_flag();
        }
    }
}
