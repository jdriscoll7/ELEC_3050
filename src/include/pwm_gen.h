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


/* 1kHz switching frequency. */
#define SWITCHING_FREQ 1000


/* Decode keypad keys to duty cycles (mapping defined by x -> x/10). */
#define KEY_TO_DUTY_CYCLE(key) ((float) (((float) (key)) / 10.0))


/* Calculates ARR for a switching frequency. */
uint16_t calculate_arr(uint32_t frequency);


/* Calculates CCR for a given auto-reload value. */
uint16_t calculate_ccr(uint16_t arr);


/* Static variable that defines current duty cycle (along with getter/setter functions). */
static uint16_t duty_cycle;
void set_duty_cycle(uint16_t new_duty_cycle);
uint16_t get_duty_cycle(void);


/* Configures timer and other relevant bits. */
void setup_pwm(void);


#endif
