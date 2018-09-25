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


int main()
{
    setup_pins();
    setup_interrupts();
    setup_keypad();
    setup_TIM10();
    
    while (1)
    {
        /* Detect if keypad has been activated recently. */
        if (check_key_pressed() == true)
        {
					  uint16_t key_pressed = get_key_pressed();
					
            switch (key_pressed)
            {
                case TIMER_ENABLE_KEY:
                    toggle_enable_TIM10();
                    break;
                
                case TIMER_CLEAR_KEY:
                    /* Only clear timer values if timer is enabled. */
                    if (TIMER_ON_OR_OFF == 0)
                    {
                        clear_timer();
                    }
                    
                    break;
            }
          
            clear_key_pressed_flag();
        }
    }
}
