#include "drivers/board.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

// TODO: make this driver more generic
#define LED_PORT_NO (1UL) // currently unused
#define LED_PIN_NO  (5UL)

// see p103 of datasheet
#define GPIO_DATA_BIT_OFFSET      (16)
#define GPIO_DIR_BIT_OFFSET       (24)

#define GPIO_BIT_MASK(shift, pin) (1UL << (uint8_t)((shift) + (pin)))

void set_led_pin_as_output()
{
    /* set P1.5 as output */
    GP1DAT |= GPIO_BIT_MASK(GPIO_DIR_BIT_OFFSET, LED_PIN_NO);
}

void turn_led_pin_off(void)
{
    /* turn P1.5 off */
    GP1DAT &= ~GPIO_BIT_MASK(GPIO_DATA_BIT_OFFSET, LED_PIN_NO);
}

void turn_led_pin_on(void)
{
    /* turn P1.5 on */
    GP1DAT |= GPIO_BIT_MASK(GPIO_DATA_BIT_OFFSET, LED_PIN_NO);
}

void toggle_led_pin(void)
{
    /* toggle P1.5 */
    GP1DAT ^= GPIO_BIT_MASK(GPIO_DATA_BIT_OFFSET, LED_PIN_NO);
}
