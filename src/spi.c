#include "spi.h"
#include "system.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

enum
{
    SPIEN                 = (1 << 0),  /* SPI enable bit */
    SPIMEN                = (1 << 1),  /* Master mode enable bit */
    SPICPH                = (1 << 2),  /* Serial clock phase mode bit */
    SPICPO                = (1 << 3),  /* Serial clock polarity mode bit */
    SPIWOM                = (1 << 4),  /* SPI wired or mode enable bit */
    SPILF                 = (1 << 5),  /* LSB first transfer enable bit */
    SPITMDE               = (1 << 6),  /* SPI transfer and interrupt mode */
    SPIZEN                = (1 << 7),  /* SPI transmit zeros when transmit FIFO is empty */
    SPIROW                = (1 << 8),  /* SPIRX overflow overwrite enable */
    SPIOEN                = (1 << 9),  /* Slave MISO output enable bit */
    SPILP                 = (1 << 10), /* Loopback enable bit */
    SPICONT               = (1 << 11), /* Continuous transfer enable */
    SPIRFLH               = (1 << 12), /* SPI receive FIFO flush enable bit */
    SPITFLH               = (1 << 13), /* SPI transmit FIFO flush enable bit */
    SPIMDE_OFFSET         = (1 << 14)  /* SPI IRQ mode bits */
};

/*
 * @brief Initializes the SPI peripheral.
 *
 * @note Pin0.1 = sck, Pin0.2 = miso, Pin0.3 = mosi
 */
extern void spi_init(const uint32_t bit_rate)
{
    /* set bit rate, see p97 of datasheet */
    SPIDIV = CPU_CLK / (2 * bit_rate) - 1;

    /* set alternative functions for P0.1, P0.2, and P0.3 */
    GP0CON0 = (1UL << 12) | (1UL << 8) | (1UL << 4);

    /* clear bit 1 of GP0CON1 for SPI mode */
    GP0KEY1 = GP0KEY1_KEY;
    GP0CON1 &= ~(1UL << 1);
    GP0KEY2 = GP0KEY2_KEY;

    /* toggle to these bits flush receive and transmit FIFO */
	SPICON = SPITFLH | SPIRFLH;

    /* initialize spi peripheral */
    SPICON = SPICONT | SPIOEN | SPIZEN | SPITMDE | \
             SPICPO  | SPICPH | SPIMEN | SPIEN;
}