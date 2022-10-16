#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void adc_init(void);
void adc_set_rate(const uint16_t rate);

#endif // ADC_H
