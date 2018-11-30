#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <stdint.h>


/* Controller parameters. */
static int32_t A0 = 29000;
static int32_t A1 = 27000;
static int32_t A2 = 230;

//static int32_t A0 = 892;
//static int32_t A1 = 913;
//static int32_t A2 = 126;


/* Voltage constants for each speed (based on tachometer amplitude measurements). */
/* Ranges from 0.45V to 1.1 V */
#define NUM_SPEEDS 11


// static uint32_t speed_to_amplitude_table[NUM_SPEEDS] = {0, 471859, 547590, 623320, 699051, 774781, 850512, 926242, 1001973, 1077703, 1153434};
static uint32_t speed_to_amplitude_table[NUM_SPEEDS] = {0, 461, 535, 609, 683, 757, 831, 905, 979, 1052, 1126};


/* Defines size of error buffer - needed for PID control. */
#define ERROR_BUFFER_SIZE 3


void controller_step(uint32_t new_error_data);
void set_desired_speed(uint16_t new_speed);


#endif
