/* - File: main.c

       - Description
           - Coordinates functionality in other files to meet specifications
             for current lab.
             
       - Author: Joe Driscoll 
*/


#include "setup.h"


/* Define on and off keys for bcd timer. */
#define TOGGLE_KEY 0xF
#define CLEAR_KEY  0xE


int main()
{
    setup_pins();
    setup_interrupts();
    setup_keypad();
    setup_pwm();
    setup_tachometer_driver();    
    
    while (1)
    {
        /* Detect if keypad has been activated recently. */
        if (check_key_pressed() == true)
        {
            /* Decode key and set the duty cycle. */
            uint16_t key_pressed = get_key_pressed();
            
            uint8_t timer_status = get_timer_status();
            
            /* See if key controls bcd timer or motor speed. */
            switch (key_pressed)
            {
                case TOGGLE_KEY:
                    if (timer_status == 0)
                    {
                        bcd_timer_on();
                    }
                    else
                    {
                        bcd_timer_off();
                    }
                    
                    break;
                    
                case CLEAR_KEY:
                    clear_bcd();
                    break;
                    
                default:
                    set_desired_speed(key_pressed);
            }
            
            /* Clear key pressed flag to make keypad controller work (tells it that key has been read). */
            clear_key_pressed_flag();
        }
    }
}
