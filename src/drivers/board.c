#include "drivers/board.h"

#include "utils/my_assert.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

#define LED_PORT (1U)
#define LED_PIN  (5U)

void set_led_pin_as_output()
{
    set_pin_as_output(LED_PORT, LED_PIN);
}

void set_pin_as_output(uint8_t port, uint8_t pin)
{
    MY_ASSERT(port <= 2);
    MY_ASSERT(pin <= 7);

    uint32_t pin_to_set = (1UL << (24 + pin));

    if(port == 0)
    {
        GP0DAT |= pin_to_set;
    }
    else if(port == 1)
    {
        GP1DAT |= pin_to_set;
    }
    else
    {
        GP2DAT |= pin_to_set;
    }
}

void turn_led_pin_off(void)
{
    /* turn P1.5 off */
    GP1DAT &= ~(1UL << (16 + 5));
}

void turn_led_pin_on(void)
{
    /* turn P1.5 on */
    GP1DAT |= (1UL << (16 + 5));
}

void toggle_led_pin(void)
{
    /* toggle P1.5 */
    GP1DAT ^= (1UL << (16 + 5));
}
