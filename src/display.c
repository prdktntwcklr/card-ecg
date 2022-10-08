#include "display.h"

#include <stdbool.h>

#include "runtime_error.h"
#include "spi.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

#define CS_PIN_NO    (0UL)
#define RESET_PIN_NO (2UL)
#define DC_PIN_NO    (4UL)

/* Flag to check if peripheral is initialized or not */
static bool display_is_initialized = false;

/* Private function declarations */
static void display_gpio_init(void);
static void display_cs_on(void);
static void display_cs_off(void);
static void display_reset_on(void);
static void display_reset_off(void);
static void display_dc_on(void);
static void display_dc_off(void);
static void display_send_command(const uint8_t byte);

/*
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

/*
 * @brief Turns the CS pin on.
 */
static void display_cs_on(void)
{
    GP0DAT |= (1UL << (16 + CS_PIN_NO));
}

/*
 * @brief Turns the CS pin off.
 */
static void display_cs_off(void)
{
    GP0DAT &= ~(1UL << (16 + CS_PIN_NO));
}

/*
 * @brief Turns the reset pin on.
 */
static void display_reset_on(void)
{
    GP0DAT |= (1UL << (16 + RESET_PIN_NO));
}

/*
 * @brief Turns the reset pin off.
 */
static void display_reset_off(void)
{
    GP0DAT &= ~(1UL << (16 + RESET_PIN_NO));
}

/*
 * @brief Turns the DC pin on.
 */
static void display_dc_on(void)
{
    GP0DAT |= (1UL << (16 + DC_PIN_NO));
}

/*
 * @brief Turns the DC pin off.
 */
static void display_dc_off(void)
{
    GP0DAT &= ~(1UL << (16 + DC_PIN_NO));
}

/*
 * @brief Sends a command to the display.
 */
static void display_send_command(const uint8_t byte)
{
    display_dc_off();
    display_cs_off();

	spi_send_data(byte);
	spi_wait_for_tx_complete();

    display_cs_on();
	display_dc_on();
}

/*
 * @brief Called by the application to initialize the display.
 */
void display_init(void)
{
    spi_init(5120000);
    display_gpio_init();

    /* TODO: perform rest of init commands */

    display_is_initialized = true;
}

/*
 * @brief Sends the framebuffer to the display.
 */
void display_send_framebuffer(const uint8_t *data)
{
    /* check if peripheral is initialized before sending data */
    if(display_is_initialized == false)
    {
        RUNTIME_ERROR("Display is not initialized!");
        return;
    }

    /* TODO: Implement rest of function */
}
