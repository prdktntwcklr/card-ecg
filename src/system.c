#include "system.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

/*
 * @brief Initializes the system by setting power and clock peripherals.
 */
extern void system_init(void)
{
    /* perform power settings */
    POWKEY1 = POWKEY1_KEY;
    POWCON0 = CLK_10240_KHZ | CORE_POWER_ON | PERIPH_POWER_ON | PLL_POWER_ON;
    POWKEY2 = POWKEY2_KEY;
}
