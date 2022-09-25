#include "main.h"
#include "aduc706x.h"
#include "led.h"
#include "stdbool.h"

#define INT_OSC            (32768UL)
#define PLL_CLK            (10240000UL)
#define SLCLK              (INT_OSC)
#define ECLK               (PLL_CLK)

#define TICK_RATE_HZ       (100UL)
#define TIMER_RELOAD_VALUE ((ECLK)/(TICK_RATE_HZ))
#define ONE_SEC_IN_MS      (1000U)
#define TIMER_INC_VALUE    ((ONE_SEC_IN_MS)/(TICK_RATE_HZ))

static void low_level_init(void);
void timer_init(void);
bool timer_deadline_reached(const uint32_t deadline);
void IRQHandler(void) __attribute__((interrupt));

static volatile uint32_t time_stamp = 0;

#ifndef TEST
int main(void)
#else
int testable_main(void)
#endif
{
    low_level_init();
    led_init();
    timer_init();
    
    while(1)
    {
        static uint32_t deadline = ONE_SEC_IN_MS;

        if(timer_deadline_reached(deadline))
        {
            deadline += ONE_SEC_IN_MS;

            led_toggle();
        }
    }

    return 0;
}

static void low_level_init(void)
{
    /* perform power settings */
    POWKEY1 = 0x1;
    POWCON0 = CLK_10240_KHZ | CORE_POWER_ON | PERIPH_POWER_ON | PLL_POWER_ON;
    POWKEY2 = 0xF4;
}

void timer_init(void)
{
    /* set up timer0 */
    T0LD  = TIMER_RELOAD_VALUE;
    T0CON = T0_10MHZ | T0_DIV_1 | T0_ENABLED | T0_DOWN | T0_PERIODIC;

    /* enable timer0 interrupt */
    IRQEN = TIMER0_BIT;
}

bool timer_deadline_reached(const uint32_t deadline)
{
    return ((int32_t)(time_stamp - deadline) >= 0);
}

void IRQHandler(void)
{
    uint32_t irq = IRQSTA;

    if(irq & TIMER0_BIT)
    {
        time_stamp += TIMER_INC_VALUE;
        T0LD  = TIMER_RELOAD_VALUE;
        T0CLRI = 0;
    }
}
