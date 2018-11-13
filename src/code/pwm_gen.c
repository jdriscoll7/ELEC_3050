/* - File: pwm_gen.c
       - Description
           - Provides a convenient interface to a PWM.
             
       - Author: Joe Driscoll 
*/


#include "pwm_gen.h"
#include "timing_functions.h"


/* Calculates ARR for a switching frequency. */
uint16_t calculate_arr(uint32_t frequency)
{
    return ((uint16_t) ((CLOCK_FREQ / (DEFAULT_PRESCALE + 1)) / frequency) - 1);
}


/* Calculates CCR given arr. */
uint16_t calculate_ccr(uint16_t arr)
{
    return ((uint16_t) ((arr + 1) * duty_cycle / 100));
}


/* Setter for duty_cycle variable. */
void set_duty_cycle(uint16_t new_duty_cycle)
{
    duty_cycle = new_duty_cycle;
    
    uint16_t arr = calculate_arr(SWITCHING_FREQ);
    
    set_timer_pwm_parameters(TIM10, calculate_ccr(arr), arr);
}


/* Getter for duty_cycle variable. */
uint16_t get_duty_cycle(void)
{
    return duty_cycle;
}


void setup_pwm(void)
{
    setup_TIM10();
    enable_timer(TIM10);
}
