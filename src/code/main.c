/* - File: main.c

       - Description
           - Coordinates functionality in other files to meet specifications
             for current lab.
             
       - Author: Joe Driscoll 
*/


#include "setup.h"


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
            set_duty_cycle(KEY_TO_DUTY_CYCLE(key_pressed));

            clear_key_pressed_flag();
        }
    }
}
