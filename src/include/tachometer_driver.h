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


/* Reference voltage for ADC is hard-set to 3V. */
#define ADC_VOLTAGE_REF 3
#define ADC_BITS 12
#define ADC_BITS_RAISED ((float) (1 << ADC_BITS))
#define ADC_STEP (((float) ADC_VOLTAGE_REF) / (ADC_BITS_RAISED - 1))


/* Used to setup tachometer driver. */
void setup_tachometer_driver(void);


/* TIM11 interrupt handler. */
void TIM11_IRQHandler(void);


/* Sets up the ADC. */
static void setup_adc(void);


#endif
