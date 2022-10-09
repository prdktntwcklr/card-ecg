#include "superloop.h"
#include "display.h"
#include "led.h"
#include "system.h"
#include "timer.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

#define ONE_SEC_IN_MS      (1000U)

extern void superloop_init(void)
{
    /* system_init() must be called first */
    system_init();

    /* initialize rest of peripherals */
    led_init();
    timer_init();
    display_init();
}

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
