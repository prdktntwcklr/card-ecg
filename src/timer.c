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

/*
 * @brief Initializes the system by setting power and clock peripherals.
 */
extern void system_init(void)
{
    /* perform power settings */
    POWKEY1 = 0x1;
    POWCON0 = CLK_10240_KHZ | CORE_POWER_ON | PERIPH_POWER_ON | PLL_POWER_ON;
    POWKEY2 = 0xF4;
}

/*
 * @brief Initializes the Timer0 peripheral.
 */
extern void timer_init(void)
{
    /* set up Timer0 */
    T0LD  = TIMER_RELOAD_VALUE;
    T0CON = T0_10MHZ | T0_DIV_1 | T0_ENABLED | T0_DOWN | T0_PERIODIC;

    /* enable Timer0 interrupt */
    IRQEN = TIMER0_BIT;
}

/*
 * @brief Increments the time stamp.
 */
extern void timer_increment_stamp(const uint32_t value)
{
    time_stamp += value;
}

/*
 * @brief Returns TRUE if the deadline has been reached or surpassed.
 */
extern bool timer_deadline_reached(const uint32_t deadline)
{
    return ((int32_t)(time_stamp - deadline) >= 0);
}

/*
 * @brief Handles the Timer0 interrupt.
 */
extern void timer_handle_interrupt(void)
{
    timer_increment_stamp(TIMER_INC_VALUE);
    T0LD = TIMER_RELOAD_VALUE; 
}
