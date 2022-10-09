#ifndef SPI_H
#define SPI_H

#include <stdint.h>

void spi_init(const uint32_t bit_rate);
void spi_wait_for_tx_complete(void);
void spi_send_data(const uint8_t data);

#endif // SPI_H
