#include "timer.h"
#include "runtime_error.h"
#include "system.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

#define TICK_RATE_HZ       (100UL)
#define TIMER_DIV_VAL      (256UL)
#define TIMER_RELOAD_VALUE ((CPU_CLK)/((TICK_RATE_HZ) * (TIMER_DIV_VAL)))
#define ONE_SEC_IN_MS      (1000U)
#define TIMER_INC_VALUE    ((ONE_SEC_IN_MS)/(TICK_RATE_HZ))

STATIC_ASSERT(TIMER_RELOAD_VALUE == 400UL, timer_reload_value_should_be_400);
STATIC_ASSERT(TIMER_INC_VALUE == 10U, timer_inc_value_should_be_10);

/* keeps track of the current time stamp, incremented on each interrupt */
static volatile uint32_t time_stamp = 0;

/* flag to check if peripheral is initialized or not */
static bool timer_is_initialized = false;

/*
 * @brief Returns the current time stamp value.
 */
static uint32_t timer_get_stamp(void)
{
    IRQEN &= ~(TIMER0_BIT);
    uint32_t temp_time_stamp = time_stamp;
    IRQEN |= TIMER0_BIT;

    return temp_time_stamp;
}

/*
 * @brief Sets the time stamp to a given value.
 *
 * @note  Helper function for unit testing.
 */
/* cppcheck-suppress unusedFunction */
__attribute__((unused)) static void timer_set_stamp(const uint32_t value)
{
    IRQEN &= ~(TIMER0_BIT);
    time_stamp = value;
    IRQEN |= TIMER0_BIT;
}

/*
 * @brief Increments the time stamp by a given value.
 *
 * @note  Helper function for unit testing.
 */
/* cppcheck-suppress unusedFunction */
__attribute__((unused)) static void timer_increment_stamp(const uint32_t value)
{
    IRQEN &= ~(TIMER0_BIT);
    time_stamp += value;
    IRQEN |= TIMER0_BIT;
}

/*
 * @brief Initializes the Timer0 peripheral.
 */
extern void timer_init(void)
{
    /* set up Timer0 */
    T0LD  = TIMER_RELOAD_VALUE;
    T0CON = T0_10MHZ | T0_DIV_256 | T0_DOWN | T0_ENABLED | T0_PERIODIC;

    /* enable Timer0 interrupt */
    IRQEN = TIMER0_BIT;

    timer_is_initialized = true;
}

/*
 * @brief Returns TRUE if the deadline has been reached or surpassed.
 */
extern bool timer_deadline_reached(const uint32_t deadline)
{
    if(timer_is_initialized == false)
    {
        RUNTIME_ERROR("Timer is not initialized!");
        return false; /* for unit tests */
    }

    return ((int32_t)(time_stamp - deadline) >= 0);
}

extern void timer_delay_10ms(void)
{
    if(timer_is_initialized == false)
    {
        RUNTIME_ERROR("Timer is not initialized!");
        return; /* for unit tests */
    }

    uint32_t deadline = timer_get_stamp() + (TIMER_INC_VALUE * 2);

    while(!timer_deadline_reached(deadline)) {}
}

/*
 * @brief Handles the Timer0 interrupt.
 */
extern void timer_handle_interrupt(void)
{
    time_stamp += TIMER_INC_VALUE;

    T0LD = TIMER_RELOAD_VALUE; 
}
