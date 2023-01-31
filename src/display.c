#include "display.h"
#include "display_registers.h"
#include "my_assert.h"
#include "spi.h"
#include "timer.h"

#include <stdbool.h>

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

#define CS_PIN_NO    (0UL)
#define RESET_PIN_NO (2UL)
#define DC_PIN_NO    (4UL)

/* flag to check if peripheral is initialized or not */
static bool display_is_initialized = false;

/* Private function declarations */
static void display_gpio_init(void);
static void display_cs_on(void);
static void display_cs_off(void);
static void display_reset_on(void);
static void display_reset_off(void);
static void display_dc_on(void);
static void display_dc_off(void);
static void display_send_command(uint8_t byte);
static void display_burst_framebuffer(uint8_t *data);

/**
 * @brief Initializes the GPIO pins for the display.
 *
 * @note  Pin0.0 = CS
 *        Pin0.2 = RESET
 *        Pin0.4 = DC
 */
static void display_gpio_init(void)
{
    /* configure P0.0 as an output and turn off */
    GP0DAT |= (1UL << (24 + CS_PIN_NO));
    display_cs_off();

    /* configure P0.2 as an output and turn off */
    GP0DAT |= (1UL << (24 + RESET_PIN_NO));
    display_reset_off();

    /* configure P0.4 as an output and turn off */
    GP0DAT |= (1UL << (24 + DC_PIN_NO));
    display_dc_off();
}

/**
 * @brief Turns the CS pin on.
 */
static void display_cs_on(void)
{
    GP0DAT |= (1UL << (16 + CS_PIN_NO));
}

/**
 * @brief Turns the CS pin off.
 */
static void display_cs_off(void)
{
    GP0DAT &= ~(1UL << (16 + CS_PIN_NO));
}

/**
 * @brief Turns the reset pin on.
 */
static void display_reset_on(void)
{
    GP0DAT |= (1UL << (16 + RESET_PIN_NO));
}

/**
 * @brief Turns the reset pin off.
 */
static void display_reset_off(void)
{
    GP0DAT &= ~(1UL << (16 + RESET_PIN_NO));
}

/**
 * @brief Turns the DC pin on.
 */
static void display_dc_on(void)
{
    GP0DAT |= (1UL << (16 + DC_PIN_NO));
}

/**
 * @brief Turns the DC pin off.
 */
static void display_dc_off(void)
{
    GP0DAT &= ~(1UL << (16 + DC_PIN_NO));
}

/**
 * @brief Sends a command to the display.
 */
static void display_send_command(uint8_t byte)
{
    display_dc_off();
    display_cs_off();

    spi_send_data(byte);
    spi_wait_for_tx_complete();

    display_cs_on();
    display_dc_on();
}

/**
 * @brief 
 */
static void display_burst_framebuffer(uint8_t *data)
{
    display_cs_off();

    const int size = DISPLAY_WIDTH * DISPLAY_HEIGHT >> 3;
    
    for (int i = 0; i < size; i++)
    {
        spi_send_data(data[i]);
    }

    spi_wait_for_tx_complete();
    
    display_cs_on();
}

/**
 * @brief Called by the application to initialize the display.
 *
 * @ref   https://www.avrfreaks.net/forum/ssd1306-lcd-initialization-commands
 */
void display_init(void)
{
    /* #lizard forgives (exclude from code complexity check) */

    spi_init(5120000);
    display_gpio_init();

    display_reset_off();
    timer_delay_10ms(); /* TODO: shorter delay possible? */
    display_reset_on();
    timer_delay_10ms(); /* TODO: shorter delay possible? */

    display_send_command(SSD1306_DISPLAY_OFF);
    
    display_send_command(SSD1306_SET_DISPLAY_CLOCK_DIV);
    display_send_command(0x80);

    display_send_command(SSD1306_SET_MULTIPLEX);
    display_send_command(0x3F);

    display_send_command(SSD1306_SET_DISPLAY_OFFSET);
    display_send_command(0x0);

    display_send_command(SSD1306_SET_START_LINE | 0x0);

    display_send_command(SSD1306_CHARGE_PUMP);
    display_send_command(0x14);

    display_send_command(SSD1306_MEMORY_MODE);
    display_send_command(0x00);

    display_send_command(SSD1306_SEG_REMAP | 0x1);

    display_send_command(SSD1306_COM_SCAN_DEC);

    display_send_command(SSD1306_SET_COM_PINS);
    display_send_command(0x12);

    display_send_command(SSD1306_SET_CONTRAST);
    display_send_command(0xCF);

    display_send_command(SSD1306_SET_PRECHARGE);
    display_send_command(0xF1);

    display_send_command(SSD1306_SET_VCOMH_DESELECT);
    display_send_command(0x40);

    display_send_command(SSD1306_DISPLAYALLON_RESUME);
    display_send_command(SSD1306_DISPLAY_NORMAL);
    display_send_command(SSD1306_DISPLAY_ON);

    display_is_initialized = true;
}

#ifdef TEST
/**
 * @brief Deinitializes the display.
 *
 * @note  Used for unit testing.
 */
/* cppcheck-suppress unusedFunction */
extern void display_deinit(void)
{
    display_is_initialized = false;
}
#endif

/**
 * @brief Sends the framebuffer to the display.
 */
/* cppcheck-suppress unusedFunction */
void display_send_framebuffer(uint8_t *data)
{
    MY_ASSERT(data);
    MY_ASSERT(display_is_initialized);

    display_send_command(SSD1306_COLUMN_ADDR);
    display_send_command(0);
    display_send_command(DISPLAY_WIDTH - 1);
    display_send_command(SSD1306_PAGE_ADDR);
    display_send_command(0);
    display_send_command(7);
    
    display_burst_framebuffer(data);
}
