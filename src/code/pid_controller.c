#include "pid_controller.h"
#include "pwm_gen.h"


/* Holds desired speed. */
static uint16_t desired_speed;


/* Used to hold past error measurements. */
uint32_t error_buffer[ERROR_BUFFER_SIZE];
uint8_t error_buffer_indx = 0;


/* Holds last control action. */
uint32_t last_control_action = 0;


/* Min and max helper macros. */
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))


void controller_step(uint32_t new_error_data)
{
    /* Update error buffer. */
    error_buffer[error_buffer_indx] = new_error_data;
    
    /* Update and make control action. */
    last_control_action = last_control_action + A0*error_buffer[0] - A1*error_buffer[1] + A2*error_buffer[2];
    
    /* Saturate control action to fit within duty cycle. */
    last_control_action = MIN(MAX(0, last_control_action), 100);
    
    /* Actually make control action. */
    set_duty_cycle(last_control_action);
    
    /* Increment error buffer index. */
    error_buffer_indx++;
}



void set_desired_speed(uint16_t new_speed)
{
    desired_speed = new_speed;
}
