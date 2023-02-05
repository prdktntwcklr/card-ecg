#ifndef SPI_H
#define SPI_H

#include <stdint.h>

void spi_init(uint32_t bit_rate);
void spi_wait_for_tx_complete(void);
void spi_send_data(uint8_t data);

#endif // SPI_H
/*** end of file ***/
