#include "display.h"
#include "display_drv.h"
#include "display_registers.h"
#include "my_assert.h"
#include "spi.h"
#include "timer.h"

#include <stdbool.h>

/* flag to check if peripheral is initialized or not */
static bool display_is_initialized = false;

/* private function declarations */
static void display_send_command(uint8_t byte);
static void display_burst_framebuffer(uint8_t *data);

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
 * @brief Sends the data of the framebuffer to the display.
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
