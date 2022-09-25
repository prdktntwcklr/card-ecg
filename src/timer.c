#ifndef TEST
#include "timer.h"

#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

#define INT_OSC            (32768UL)
#define PLL_CLK            (10240000UL)
#define SLCLK              (INT_OSC)
#define ECLK               (PLL_CLK)

#define TICK_RATE_HZ       (100UL)
#define TIMER_RELOAD_VALUE ((ECLK)/(TICK_RATE_HZ))
#define ONE_SEC_IN_MS      (1000U)
#define TIMER_INC_VALUE    ((ONE_SEC_IN_MS)/(TICK_RATE_HZ))

static volatile uint32_t time_stamp = 0;

extern void timer_init(void)
{
    /* set up timer0 */
    T0LD  = TIMER_RELOAD_VALUE;
    T0CON = T0_10MHZ | T0_DIV_1 | T0_ENABLED | T0_DOWN | T0_PERIODIC;

    /* enable timer0 interrupt */
    IRQEN = TIMER0_BIT;
}

extern void timer_increment_stamp(const uint32_t value)
{
    time_stamp += value;
}

extern bool timer_deadline_reached(const uint32_t deadline)
{
    return ((int32_t)(time_stamp - deadline) >= 0);
}

extern void timer_handle_interrupt(void)
{
    timer_increment_stamp(TIMER_INC_VALUE);
    T0LD = TIMER_RELOAD_VALUE;    
}
