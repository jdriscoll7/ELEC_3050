/* - File: pwm_gen.c
       - Description
           - Provides a convenient interface to a PWM.
             
       - Author: Joe Driscoll 
*/


#include "pwm_gen.h"
#include "timing_functions.h"


/* Static variable that defines current duty cycle (along with getter/setter functions). */
static float duty_cycle;


/* Calculates ARR for a switching frequency. */
uint16_t calculate_arr(uint32_t frequency)
{
    return ((uint16_t) ((CLOCK_FREQ / (DEFAULT_PRESCALE + 1)) / frequency) - 1);
}


/* Calculates CCR given arr. */
uint16_t calculate_ccr(uint16_t arr)
{
    return ((uint16_t) ((arr + 1) * duty_cycle));
}


/* Setter for duty_cycle variable. */
void set_duty_cycle(float new_duty_cycle)
{
    duty_cycle = new_duty_cycle;
    
    uint16_t arr = calculate_arr(SWITCHING_FREQ);
    
    set_timer_pwm_parameters(TIM10, calculate_ccr(arr), arr);
}


/* Getter for duty_cycle variable. */
float get_duty_cycle(void)
{
    return duty_cycle;
}


void setup_pwm(void)
{
    setup_TIM10();
}
