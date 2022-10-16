#ifndef DAC_H
#define DAC_H

#include <stdint.h>

void dac_init(void);
void dac_set(const uint16_t dac_value);

#endif // DAC_H