#include "led.h"

#include <stdbool.h>

#include "drivers/board.h"
#include "utils/my_assert.h"

/* Flag to check if peripheral is initialized or not */
static bool led_is_initialized = false;

/**
 * @brief Initializes the LED.
 */
extern void led_init(void)
{
    set_led_pin_as_output();

    led_is_initialized = true;

    led_off();
}

#ifdef TEST
/**
 * @brief Deinitializes the LED.
 *
 * @note  Used for unit testing.
 */
/* cppcheck-suppress unusedFunction */
void led_deinit(void)
{
    led_is_initialized = false;
}
#endif

/**
 * @brief Turns the LED off.
 */
extern void led_off(void)
{
    MY_ASSERT(led_is_initialized);

    turn_led_pin_off();
}

/**
 * @brief Turns the LED on.
 */
/* cppcheck-suppress unusedFunction */
extern void led_on(void)
{
    MY_ASSERT(led_is_initialized);

    turn_led_pin_on();
}

/**
 * @brief Toggles the LED between on and off state.
 */
extern void led_toggle(void)
{
    MY_ASSERT(led_is_initialized);

    toggle_led_pin();
}
/*** end of file ***/
