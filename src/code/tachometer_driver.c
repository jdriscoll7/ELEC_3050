/* - File: tachometer_driver.c

       - Description
           - Provides interface to tachometer measurements.
             
       - Author: Joe Driscoll 
*/


#include "STM32L1xx.h"
#include "timing_functions.h"


double current_period;


/* Function fed to TIM11 interrupt handler. Updates the current_period. */
static void update_tach_period(void)
{
    /* Calculate period based on timer count. */
    double percent_period = ((double) TIM11->CNT) / (TIM11->ARR + 1);
    set_tach_period(percent_period * DEFAULT_PERIOD);   
    
    /* Reset count value. */
    clear_timer(TIM11);
}


/* Used to setup tachometer driver. */
void setup_tachometer_driver(void)
{
    /* Setup timer and set function defined in this file to handler. */
    setup_TIM11();
    //function_ptr function_array = {update_tach_period};
    //set_timer_functions(TIM11, function_array, 1);
    
    enable_timer(TIM11);
}


/* Used to update current period of tachometer. */
void set_tach_period(double new_period)
{
    current_period = new_period;
}


/* Get latest period measurement of tachometer driver. */
double get_tach_period(void)
{
    return current_period;
}
