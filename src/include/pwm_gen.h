/* - File: pwm_gen.h 
       - Description
           - Provides a convenient interface to a PWM.
             
       - Author: Joe Driscoll 
*/


#ifndef PWM_GEN_H
#define PWM_GEN_H


#include <stdint.h>
#include <stdbool.h>
#include "STM32L1xx.h"
#include "pin_definitions.h"


/* Output PWM on PA6. */
#define PWM_OUTPUT_PIN 6


/* 1kHz switching frequency. */
#define SWITCHING_FREQ 1000


/* Decode keypad keys to duty cycles (mapping defined by x -> x/10). */
#define KEY_TO_DUTY_CYCLE(key) ((float) (((float) (key)) / 10.0))


/* Provides pin, clock, and initialization setup for the PWM. */
void setup_pwm(void);


#endif
