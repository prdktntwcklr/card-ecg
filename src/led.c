#include "led.h"

#include <stdbool.h>

#include "runtime_error.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

/* Flag to check if peripheral is initialized or not */
static bool led_is_initialized = false;

/*
 * @brief Initializes the LED.
 */
extern void led_init(void)
{
    /* configure P1.5 as an output */
    GP1DAT |=  (1UL << 29);

    led_is_initialized = true;

    led_off();
}

#ifdef TEST
/*
 * @brief Deinitializes the LED.
 *
 * @note  Used for unit testing.
 */
static void led_deinit(void)
{
    led_is_initialized = false;
}
#endif

/*
 * @brief Turns the LED off.
 */
extern void led_off(void)
{
    if(led_is_initialized == false)
    {
        RUNTIME_ERROR("Led is not initialized!");
        return; /* for unit tests */
    }

    GP1DAT &= ~(1UL << 21);
}

/*
 * @brief Turns the LED on.
 */
/* cppcheck-suppress unusedFunction */
extern void led_on(void)
{
    if(led_is_initialized == false)
    {
        RUNTIME_ERROR("Led is not initialized!");
        return; /* for unit tests */
    }

    GP1DAT |= (1UL << 21);
}

/*
 * @brief Toggles the LED between on and off state.
 */
extern void led_toggle(void)
{
    if(led_is_initialized == false)
    {
        RUNTIME_ERROR("Led is not initialized!");
        return; /* for unit tests */
    }

    GP1DAT ^= (1UL << 21);
}
