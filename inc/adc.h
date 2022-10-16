#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void adc_init(void);
void adc_set_rate(const uint16_t rate);
void adc_set_gain(const uint16_t adc_gain);

#endif // ADC_H
