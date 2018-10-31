/* - File: tachometer_driver.h 

       - Description
           - Provides interface to tachometer measurements.
             
       - Author: Joe Driscoll 
*/


#include "pin_definitions.h"
#include "stdint.h"


#ifndef TACHOMETER_DRIVER_H
#define TACHOMETER_DRIVER_H


/* Reference voltage for ADC is hard-set to 3V. */
#define ADC_VOLTAGE_REF 3
#define ADC_BITS 12
#define ADC_BITS_RAISED ((float) (1 << ADC_BITS))
#define ADC_STEP (((float) ADC_VOLTAGE_REF) / (ADC_BITS_RAISED - 1))


#define MA_WINDOW_SIZE 100


/* Moving average filter for measurement filtering. */
typedef struct 
{
    int n;
    int current_index;
    float current_value;
    uint16_t input_buffer[MA_WINDOW_SIZE];
    
} filter_t;

/* Functions that operate on filter_t */
filter_t *create_ma_filter(void);
void update_ma_filter(filter_t *filter, uint16_t input_value);
float get_ma_output(filter_t *filter);


/* Used to setup tachometer driver. */
void setup_tachometer_driver(void);


/* Get latest period measurement of tachometer driver. */
float get_tach_period(void);


/* TIM11 interrupt handler. */
void TIM11_IRQHandler(void);


/* Sets up the ADC. */
static void setup_adc(void);


/* ADC interrupt handler for amplitude measurements. */
void ADC1_IRQHandler(void);


#endif
