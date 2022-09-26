#include "spi.h"
#include "system.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

// Pin <0,1> sck;
// Pin <0,2> miso;
// Pin <0,3> mosi;

/*
 * @brief Initializes the SPI peripheral.
 */
extern void spi_init(const uint32_t bit_rate)
{
    SPIDIV = CPU_CLK / (2 * bit_rate) - 1;

    /* set alternative functions for P0.1, P0.2, and P0.3 */
    GP0CON0 = (1UL << 12) | (1UL << 8) | (1UL << 4);

    /* clear bit 1 of GP0CON1 for SPI mode */
    GP0KEY1 = GP0KEY1_KEY;
    GP0CON1 &= ~(1UL << 1);
    GP0KEY2 = GP0KEY2_KEY;

    
}