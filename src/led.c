#include "led.h"
#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

/*
 * @brief Initializes the LED.
 */
extern void led_init(void)
{
    GP1DAT |=  (1 << 29); /* configure P1.5 as an output */
    led_off();
}

/*
 * @brief Turns the LED off.
 */
extern void led_off(void)
{
    GP1DAT &= ~(1 << 21); /* turn P1.5 off */
}

/*
 * @brief Turns the LED on.
 */
extern void led_on(void)
{
    GP1DAT |= (1 << 21); /* turn P1.5 on */
}

/*
 * @brief Toggles the LED between on and off state.
 */
extern void led_toggle(void)
{
    GP1DAT ^= (1 << 21); /* toggle P1.5 */
}
