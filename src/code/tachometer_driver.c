/* - File: tachometer_driver.c

       - Description
           - Provides interface to tachometer measurements.
             
       - Author: Joe Driscoll 
*/


#include "STM32L1xx.h"
#include "timing_functions.h"
#include "stdlib.h"
#include "pin_definitions.h"
#include "keypad_driver.h"    


/* Allows data acquisition to be turned on and off. */
#if DATA_ACQUISITION_MODE

#define DATA_ACQUISITION_TIME        5
#define DATA_ACQUISITION_BUFFER_SIZE (DATA_ACQUISITION_TIME * 100)

uint16_t data_acquisition_buffer[DATA_ACQUISITION_BUFFER_SIZE];
uint32_t data_acquisition_index = 0;

#endif



/* Keep period estimations different for frequency and amplitude measurements. */
static filter_t *amplitude_filter;


/* Creates a filter. */
filter_t *create_ma_filter(void)
{
    filter_t *new_filter = (filter_t *) malloc(sizeof(filter_t));
    
    /* Set filter buffer to all zeros then set it to struct. */
    for (unsigned int i = 0; i < MA_WINDOW_SIZE; i++)
    {
        new_filter->input_buffer[i] = 0;
    }
    
    /* Set default values. */
    new_filter->current_value = 0;
    new_filter->current_index = 0;
    new_filter->n = MA_WINDOW_SIZE;
    
    return new_filter;
}


/* Feed input values into a filter. */
void update_ma_filter(filter_t *filter, uint32_t input_value)
{
    /* Increment index. */
    filter->current_index = MOD(filter->current_index + 1, filter->n);
    
    /* y(t) = y(t-1) + (1/n)(x(t) - x(t-n) */
    uint32_t value_to_remove = filter->input_buffer[MOD(filter->current_index + filter->n, filter->n)];
    filter->current_value += (input_value - value_to_remove) / filter->n;
    
    /* Update input buffer. */
    filter->input_buffer[filter->current_index] = input_value;
}



uint32_t get_ma_output(filter_t *filter)
{
    return filter->current_value;
}


/* Used to setup tachometer driver. */
void setup_tachometer_driver(void)
{
    /* Setup filters. */
    amplitude_filter = create_ma_filter();
    
    /* Setup ADC for amplitude measurements. */
    setup_adc();
    
    /* Setup timer and set function defined in this file to handler. */
    setup_TIM11();
    
    enable_timer(TIM11);
}


/* Get latest period measurement of tachometer driver. */
uint32_t get_tach_period(void)
{
    return get_ma_output(amplitude_filter);
}


/* TIM11 interrupt handler - triggers ADC measurement. */
void TIM11_IRQHandler(void)
{
    /* Start first conversion. */
    ADC1->CR2 |= ADC_CR2_SWSTART;
    
    /* Wait for EOC. */
    while((ADC1->SR & ADC_SR_EOC) == 0);
    
    /* Do some data recording if data acquisition mode is on. */
    #if DATA_ACQUISITION_MODE
       
    if ((data_acquisition_index < DATA_ACQUISITION_BUFFER_SIZE) && (get_key_pressed() == 0xA) || get_key_pressed() == 0x8)
    {
        data_acquisition_buffer[data_acquisition_index++] = ADC1->DR;   
    }
    else if (get_key_pressed() == 0x0)
    {
        data_acquisition_index = 0;
    }
    
    #endif
    
    /* Inputs an amplitude measurement into the moving average filter. */
    update_ma_filter(amplitude_filter, ((uint32_t) ADC1->DR) << 20);
    
    /* Need to make control step here. */
    
       
    /* Need to increment BCD counter. */
       
       
    /* Clear EOC to be safe. */
    ADC1->SR &= ~(0x2);
    
    clear_timer(TIM11);
    clear_TIM11_interrupt();
}


/* Sets up the ADC. */
static void setup_adc(void)
{
    /* Turn on clock to ADC. */
    RCC->APB2ENR |= (0x1 << 9);
    
    /* Make ADC use PA0 as channel. */
    ADC1->SQR5 &= ~ADC_SQR5_SQ1;
    
    /* Turn on ADC and wait for power on. */
    ADC1->CR2 |= ADC_CR2_ADON;
    while((ADC1->SR & ADC_SR_ADONS) == 0);
    
}
