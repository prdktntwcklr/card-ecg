#include "system.h"
#include "my_assert.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

STATIC_ASSERT(CPU_CLK == 10240000UL, cpu_clk_should_be_10240_khz);
STATIC_ASSERT(INT_OSC == 32768UL, int_osc_should_be_32768_hz);

/**
 * @brief Initializes the system by setting power and clock peripherals.
 */
extern void system_init(void)
{
    /* perform power settings */
    POWKEY1 = POWKEY1_KEY;
    POWCON0 = CLK_10240_KHZ | CORE_POWER_ON | PERIPH_POWER_ON | PLL_POWER_ON;
    POWKEY2 = POWKEY2_KEY;
}
