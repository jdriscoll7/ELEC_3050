#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H


/* Controller parameters. */
#define A0 1
#define A1 1
#define A2 1


/* Voltage constants for each speed (based on tachometer amplitude measurements). */
/* Ranges from 0.45V to 1.1 V */
#define NUM_SPEEDS 10

static uint32_t speed_to_amplitude_table[NUM_SPEEDS] = {471859, 547590, 623320, 699051, 774781, 850512, 926242, 1001973, 1077703, 1153434};


/* Miscillaneous definitions. */
#define ERROR_BUFFER_SIZE 3


void controller_step(uint32_t new_data);
void set_desired_speed(uint16_t new_speed);


#endif
