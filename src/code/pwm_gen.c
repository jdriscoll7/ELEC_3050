/* - File: pwm_gen.c
       - Description
           - Provides a convenient interface to a PWM.
             
       - Author: Joe Driscoll 
*/


/* Static variable that defines current duty cycle (along with getter/setter functions). */
static float duty_cycle;


/* Setter for duty_cycle variable. */
void set_duty_cycle(float new_value)
{
    duty_cycle = new_value;
}


/* Getter for duty_cycle variable. */
float get_duty_cycle(void)
{
    return duty_cycle;
}


/* Function for determining output value of pwm. */
uint16_t get_pwm_output(float time)
{
    /* What percent of the period is completed? */
    float portion_completed = time * SWITCHING_FREQ;
    
    /* Off if time is past the on portion of pulse, on otherwise. */
    return ((portion_completed > duty_cycle) ? 0 : 1)
}


#endif
