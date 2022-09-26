#include "spi.h"
#include "system.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

/*
 * @brief Initializes the SPI peripheral.
 */
extern void spi_init(const uint32_t bit_rate)
{
    SPIDIV = CPU_CLK / (2 * bit_rate) - 1;
}