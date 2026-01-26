#include "drivers/board.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

void set_led_pin_as_output(void)
{
    /* configure P1.5 as an output */
    GP1DAT |= (1UL << 29);
}

void turn_led_pin_off(void)
{
    /* turn P1.5 off */
    GP1DAT &= ~(1UL << 21);
}

void turn_led_pin_on(void)
{
    /* turn P1.5 on */
    GP1DAT |= (1UL << 21);
}

void toggle_led_pin(void)
{
    /* toggle P1.5 */
    GP1DAT ^= (1UL << 21);
}
