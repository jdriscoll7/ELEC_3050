/* - File: tachometer_driver.h 

       - Description
           - Provides interface to tachometer measurements.
             
       - Author: Joe Driscoll 
*/


#ifndef TACHOMETER_DRIVER_H
#define TACHOMETER_DRIVER_H


/* Function fed to TIM11 interrupt handler. Updates the current_period. */
static void update_tach_period(void);


/* Used to setup tachometer driver. */
void setup_tachometer_driver(void);


/* Used to update current period of tachometer. */
void set_tach_period(double new_period);


/* Get latest period measurement of tachometer driver. */
double get_tach_period(void);


/* TIM11 interrupt handler. */
void TIM11_IRQHandler(void);

#endif
