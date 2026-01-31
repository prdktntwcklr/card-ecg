#include "drivers/board.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

// TODO: make this driver more generic

#define LED_PIN (5)

void set_led_pin_as_output()
{
    /* set P1.5 as output */
    GP1DAT |= (1UL << (24 + LED_PIN));
}

void turn_led_pin_off(void)
{
    /* turn P1.5 off */
    GP1DAT &= ~(1UL << (16 + LED_PIN));
}

void turn_led_pin_on(void)
{
    /* turn P1.5 on */
    GP1DAT |= (1UL << (16 + LED_PIN));
}

void toggle_led_pin(void)
{
    /* toggle P1.5 */
    GP1DAT ^= (1UL << (16 + LED_PIN));
}
