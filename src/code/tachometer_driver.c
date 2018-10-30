/* - File: tachometer_driver.c

       - Description
           - Provides interface to tachometer measurements.
             
       - Author: Joe Driscoll 
*/


#include "STM32L1xx.h"
#include "timing_functions.h"
#include "stdlib.h"
#include "pin_definitions.h"


/* Keep period estimations different for frequency and amplitude measurements. */
static ma_filter_t *period_filter;
static ma_filter_t *amplitude_filter;


/* Creates a filter. */
ma_filter_t *create_ma_filter(unsigned int n)
{
    /* Allocate memory. */
    float *filter_input_buffer = (float *) malloc(n*sizeof(float));
    ma_filter_t *new_filter = (ma_filter_t *) malloc(sizeof(ma_filter_t));
    
    /* Set filter buffer to all zeros then set it to struct. */
    for (unsigned int i = 0; i < n; i++)
    {
        filter_input_buffer[i] = 0;
    }
    
    new_filter->input_buffer = filter_input_buffer;
    
    /* Set default values. */
    new_filter->current_value = 0;
    new_filter->current_index = 0;
    new_filter->n = n;
    
    return new_filter;
}


/* Feed input values into a filter. */
void update_ma_filter(ma_filter_t *filter, float input_value)
{
    /* Increment index. */
    filter->current_index = MOD(filter->current_index + 1, filter->n);
    
    /* y(t) = y(t-1) + (1/n)(x(t) - x(t-n) */
	  float value_to_remove = filter->input_buffer[MOD(filter->current_index + filter->n, filter->n)];
    filter->current_value += (input_value - value_to_remove) / filter->n;
    
    /* Update input buffer. */
    filter->input_buffer[filter->current_index] = input_value;
}



float get_ma_output(ma_filter_t *filter)
{
    return filter->current_value;
}


/* Used to setup tachometer driver. */
void setup_tachometer_driver(void)
{
    /* Setup filters. */
    amplitude_filter = create_ma_filter(MA_WINDOW_SIZE);
		period_filter = create_ma_filter(MA_WINDOW_SIZE);
    
    /* Setup ADC for amplitude measurements. */
    setup_adc();
    
	  /* Setup timer and set function defined in this file to handler. */
    setup_TIM11();
	
    enable_timer(TIM11);
}


/* Get latest period measurement of tachometer driver. */
float get_tach_period(void)
{
    return get_ma_output(amplitude_filter);
}


/* TIM11 interrupt handler - calculates period based on period measurements. */
void TIM11_IRQHandler(void)
{
    /* Calculate period based on signal frequency measurements. */
    float percent_period = ((float) TIM11->CCR1) / (TIM11->ARR + 1);
    update_ma_filter(period_filter, percent_period * TIM11_DEFAULT_PERIOD);
    clear_timer(TIM11);
    
    clear_TIM11_interrupt();
}


/* Sets up the ADC. */
static void setup_adc(void)
{
    /* Turn on clock to ADC. */
    RCC->APB2ENR |= (0x1 << 9);
    
    /* Make end of conversion (EOC) signal interrupt CPU. */
    ADC1->CR1 |= ADC_CR1_EOCIE;
    
    /* Turn on continuous conversion. */
    ADC1->CR2 |= (0x1 << 1);
    
    /* Make ADC use PA0 as channel. */
    ADC1->SQR5 &= ~ADC_SQR5_SQ1;
    
    /* Make ADC sample once every 96 cycles.  */
    ADC1->SMPR3 |= 0x5;
    
    /* Enable interrupt in NVIC. */
    NVIC_EnableIRQ(ADC1_IRQn);
    
		/* Turn on ADC and wait for power on. */
    ADC1->CR2 |= ADC_CR2_ADON;
    while((ADC1->SR & ADC_SR_ADONS) == 0);
	
    /* Start first conversion. */
    ADC1->CR2 |= ADC_CR2_SWSTART;
}


/* ADC interrupt handler for amplitude measurements. */
void ADC1_IRQHandler(void)
{
    /* Inputs an amplitude measurement into the moving average filter. */
    update_ma_filter(amplitude_filter, ADC_STEP * ((float) ADC1->DR));
	
	  /* Clear interrupt pending. */
	  NVIC_ClearPendingIRQ(ADC1_IRQn);
	
	  /* Clear EOC to be safe. */
	  ADC1->SR &= ~(0x2);
}
