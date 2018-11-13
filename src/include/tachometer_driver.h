/* - File: tachometer_driver.h 

       - Description
           - Provides interface to tachometer measurements.
             
       - Author: Joe Driscoll 
*/


#include "pin_definitions.h"
#include "stdint.h"


#ifndef TACHOMETER_DRIVER_H
#define TACHOMETER_DRIVER_H


/* Turns data acquisition on and off. */
#define DATA_ACQUISITION 0


/* Number of samples in moving average window. */
#define MA_WINDOW_SIZE 10


/* Reference voltage for ADC is hard-set to 3V. */
#define ADC_VOLTAGE_REF 3
#define ADC_BITS 12
#define ADC_BITS_RAISED ((float) (1 << ADC_BITS))
#define ADC_STEP (((float) ADC_VOLTAGE_REF) / (ADC_BITS_RAISED - 1))


/* Voltage constants for each speed (based on tachometer amplitude measurements). */
/* Ranges from 0.45V to 1.1 V */
#define NUM_SPEEDS 10
uint32_t speed_to_amplitude_table[NUM_SPEEDS] = {471859, 547590, 623320.177777778, 699050.666666667, 774781.155555556, 850511.644444444, 926242.133333333, 1001972.62222222, 1077703.11111111, 1153433.60000000}


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


#endif
