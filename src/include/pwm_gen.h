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


/* Static variable that defines current duty cycle (along with getter/setter functions). */
static float duty_cycle;
void set_duty_cycle(float new_value);
float get_duty_cycle(void);


/* Function for determining output value of pwm. */
uint16_t get_pwm_output(float time);


/* Provides pin, clock, and initialization setup for the PWM. */
void setup_pwm(void);


#endif
