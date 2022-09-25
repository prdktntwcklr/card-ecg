#include "system.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

extern void system_init(void)
{
    /* perform power settings */
    POWKEY1 = 0x1;
    POWCON0 = CLK_10240_KHZ | CORE_POWER_ON | PERIPH_POWER_ON | PLL_POWER_ON;
    POWKEY2 = 0xF4;
}
