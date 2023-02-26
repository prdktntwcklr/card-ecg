#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void adc_init(void);
void adc_start(void);
void adc_stop(void);
int32_t adc_get(void);
void adc_set_rate(uint16_t rate);
void adc_set_gain(uint16_t adc_gain);
void adc_handle_interrupt(void);

#endif // ADC_H
/*** end of file ***/
