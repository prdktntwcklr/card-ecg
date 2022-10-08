#include "display.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

#define CS_PIN_NO    (0UL)
#define RESET_PIN_NO (2UL)
#define DC_PIN_NO    (4UL)

static void display_gpio_init(void);
static void display_cs_on(void);
static void display_cs_off(void);
static void display_reset_on(void);
static void display_reset_off(void);
static void display_dc_on(void);
static void display_dc_off(void);

/*
 * @brief Initializes the GPIO pins for the display.
 *
 * @note  Pin0.0 = cs
 *        Pin0.2 = reset
 *        Pin0.4 = dc
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

static void display_cs_on(void)
{
    GP0DAT |= (1UL << (16 + CS_PIN_NO));
}

static void display_cs_off(void)
{
    GP0DAT &= ~(1UL << (16 + CS_PIN_NO));
}

static void display_reset_on(void)
{
    GP0DAT |= (1UL << (16 + RESET_PIN_NO));
}

static void display_reset_off(void)
{
    GP0DAT &= ~(1UL << (16 + RESET_PIN_NO));
}

static void display_dc_on(void)
{
    GP0DAT |= (1UL << (16 + DC_PIN_NO));
}

static void display_dc_off(void)
{
    GP0DAT &= ~(1UL << (16 + DC_PIN_NO));
}
