#include "pid_controller.h"
#include "pwm_gen.h"
#include "pin_definitions.h"


/* Holds desired speed. */
static uint16_t desired_speed;


/* Used to hold past error measurements. */
int64_t error_buffer[ERROR_BUFFER_SIZE];
uint8_t error_buffer_indx = 0;


/* Holds last control action. */
int64_t last_control_action = 0;


/* Min and max helper macros. */
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))


void controller_step(uint32_t speed_data)
{
    
    if (desired_speed == 0)
    {
        set_duty_cycle(0);
    }
    else if (desired_speed == 10)
    {
        set_duty_cycle(100);
    }
    else
    {
        /* Update error buffer. */
        error_buffer[error_buffer_indx] = (int64_t) (((int64_t) speed_to_amplitude_table[desired_speed]) - ((int64_t) speed_data));

        #if TUNING_MODE
        
        /* Calculate A0, A1, A2 dynamically in terms of constants. */
        //int64_t new_A0 = (Kp) + (Ki) + (100 * (Kd));
        //int64_t new_A1 = (Kp) + (200 * (Kd)) - ((Ki) / 200);
        //int64_t new_A2 = (Kd) * 100;
        
        /* Update and make control action. */
        int64_t err0 =  (error_buffer[MOD(error_buffer_indx, ERROR_BUFFER_SIZE)] * Kp)
                      + (error_buffer[MOD(error_buffer_indx, ERROR_BUFFER_SIZE)] * (Ki) / 200
                      + (error_buffer[MOD(error_buffer_indx, ERROR_BUFFER_SIZE)] * (100 * (Kd))));
        int64_t err1 =  (error_buffer[MOD(error_buffer_indx - 1, ERROR_BUFFER_SIZE)] * Kp)
                      - (error_buffer[MOD(error_buffer_indx - 1, ERROR_BUFFER_SIZE)] * (Ki) / 200)
                      + (error_buffer[MOD(error_buffer_indx - 1, ERROR_BUFFER_SIZE)] * (200 * (Kd)));
        int64_t err2 = error_buffer[MOD(error_buffer_indx - 2, ERROR_BUFFER_SIZE)] * (Kd*100);
        
        last_control_action = last_control_action + err0 - err1 + err2;

        
        #else
        
        /* Update and make control action normally. */
        last_control_action = last_control_action + (((A0*error_buffer[MOD(error_buffer_indx, ERROR_BUFFER_SIZE)]) 
                                                  -   (A1*error_buffer[MOD(error_buffer_indx - 1, ERROR_BUFFER_SIZE)]) 
                                                  +   (A2*error_buffer[MOD(error_buffer_indx - 2, ERROR_BUFFER_SIZE)])) >> 10);

        #endif
        
        
        /* Saturate control action to fit within duty cycle. */
        last_control_action = MIN(MAX(0, last_control_action), 100);

        /* Actually make control action. */
        set_duty_cycle(last_control_action);

        /* Increment error buffer index. */
        error_buffer_indx = MOD(error_buffer_indx + 1, ERROR_BUFFER_SIZE);
    }
}



void set_desired_speed(uint16_t new_speed)
{
    desired_speed = new_speed;
    
    error_buffer[0] = 0;
    error_buffer[1] = 0;
    error_buffer[2] = 0;
}
