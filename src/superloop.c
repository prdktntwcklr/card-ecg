#include "superloop.h"
#include "display.h"
#include "framebuffer.h"
#include "led.h"
#include "logo.h"
#include "my_assert.h"
#include "my_printf.h"
#include "system.h"
#include "timer.h"
#include "uart.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

#define ONE_SEC_IN_MS (1000U)

STATIC_ASSERT(DISPLAY_WIDTH == FRAMEBUFFER_WIDTH, display_and_framebuffer_widths_do_not_match);
STATIC_ASSERT(DISPLAY_HEIGHT == FRAMEBUFFER_HEIGHT, display_and_framebuffer_heights_do_not_match);

/**
 * @brief Runs once at the beginning of the program.
 */
extern void superloop_init(void)
{
    /* system_init() must be called first */
    system_init();

    /* initialize rest of peripherals */
    led_init();
    timer_init();
    display_init();
    framebuffer_init();

    uart_init();
    MY_PRINTF("superloop_init() complete.\r\n");
}

/**
 * @brief Runs continuously.
 */
extern bool superloop_run(void)
{
    static uint32_t deadline = ONE_SEC_IN_MS;

    if(timer_deadline_reached(deadline))
    {
        deadline += ONE_SEC_IN_MS;

        led_toggle();
    }

    return true;
}
/*** end of file ***/
