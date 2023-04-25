#include "spi.h"

#include <stdbool.h>

#include "my_assert.h"
#include "system.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

/* flag to check if peripheral is initialized or not */
static bool spi_is_initialized = false;

/* static function prototypes */
static void spi_wait_for_space_in_tx_fifo(void);

/**
 * @brief Initializes the SPI peripheral.
 *
 * @note  Pin0.1 = SCK
 *        Pin0.2 = MISO
 *        Pin0.3 = MOSI
 */
extern void spi_init(uint32_t bit_rate)
{
    MY_ASSERT(bit_rate != 0U);

    /* set bit rate, see p97 of datasheet */
    /* cppcheck-suppress zerodivcond */
    SPIDIV = (CPU_CLK / (2UL * bit_rate)) - 1UL;

    /* set alternative functions for P0.1, P0.2, and P0.3 */
    GP0CON0 |= (1UL << 12) | (1UL << 8) | (1UL << 4);

    /* clear bit 1 of GP0CON1 for SPI mode */
    GP0KEY1 = GP0KEY1_KEY;
    GP0CON1 &= ~(1UL << 1);
    GP0KEY2 = GP0KEY2_KEY;

    /* toggle to these bits flush receive and transmit FIFO */
    SPICON = SPITFLH | SPIRFLH;

    /* initialize spi peripheral */
    SPICON =
        SPICONT | SPIOEN | SPIZEN | SPITMDE | SPICPO | SPICPH | SPIMEN | SPIEN;

    spi_is_initialized = true;
}

#ifdef TEST
/**
 * @brief Deinitilizes the SPI module.
 *
 * @note  Used for unit testing.
 */
/* cppcheck-suppress unusedFunction */
static void spi_deinit(void)
{
    spi_is_initialized = false;
}
#endif

/**
 * @brief Blocks until transmit FIFO is empty.
 */
extern void spi_wait_for_tx_complete(void)
{
    while((SPISTA & 0xE) == 0xE)
    {
    }
}

/**
 * @brief Blocks until there is space in FIFO.
 */
static void spi_wait_for_space_in_tx_fifo(void)
{
    while((SPISTA & 0x8) == 0x8)
    {
    }
}

/**
 * @brief Sends data through SPI.
 */
extern void spi_send_data(uint8_t data)
{
    MY_ASSERT(spi_is_initialized);

    /* block until there is space in fifo */
    spi_wait_for_space_in_tx_fifo();

    SPITX = data;
}
/*** end of file ***/
