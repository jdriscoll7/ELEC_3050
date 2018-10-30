/* - File: tachometer_driver.h 

       - Description
           - Provides interface to tachometer measurements.
             
       - Author: Joe Driscoll 
*/


#include "pin_definitions.h"


#ifndef TACHOMETER_DRIVER_H
#define TACHOMETER_DRIVER_H


/* Reference voltage for ADC is hard-set to 3V. */
#define ADC_VOLTAGE_REF 3
#define ADC_BITS 12
#define ADC_BITS_RAISED ((double) (1 << ADC_BITS))
#define ADC_STEP (((double) ADC_VOLTAGE_REF) / ADC_BITS_RAISED)

#define MA_WINDOW_SIZE 3


/* Moving average filter for measurement filtering. */
typedef struct 
{
    int n;
    int current_index;
    double current_value;
    double *input_buffer;
    
} ma_filter_t;

/* Functions that operate on ma_filter_t */
ma_filter_t *create_ma_filter(unsigned int n);
void update_ma_filter(ma_filter_t *filter, double input_value);
double get_ma_output(ma_filter_t *filter);


/* Used to setup tachometer driver. */
void setup_tachometer_driver(void);


/* Get latest period measurement of tachometer driver. */
double get_tach_period(void);


/* TIM11 interrupt handler. */
void TIM11_IRQHandler(void);


/* Sets up the ADC. */
static void setup_adc(void);


/* ADC interrupt handler for amplitude measurements. */
void ADC1_IRQHandler(void);


#endif
