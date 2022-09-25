#include "ADuC706x.h"
#include "stdbool.h"

#define INT_OSC            (32768UL)
#define PLL_CLK            (10240000UL)
#define SLCLK              (INT_OSC)
#define ECLK               (PLL_CLK)

#define TICK_RATE_HZ       (100UL)
#define TIMER_RELOAD_VALUE ((ECLK)/(TICK_RATE_HZ))
#define ONE_SEC_IN_MS      (1000U)
#define TIMER_INC_VALUE    ((ONE_SEC_IN_MS)/(TICK_RATE_HZ))

void led_init(void);
void led_toggle(void);
bool timer_deadline_reached(const uint32_t deadline);
void IRQHandler(void) __attribute__((interrupt));

static volatile uint32_t time_stamp = 0;

int main(void)
{
    /* perform power settings */
    POWKEY1 = 0x1;
    POWCON0 = CLK_10240_KHZ | CORE_POWER_ON | PERIPH_POWER_ON | PLL_POWER_ON;
    POWKEY2 = 0xF4;

    led_init();

    /* set up timer0 */
    T0LD  = (ECLK)/(TICK_RATE_HZ);
    T0CON = T0_10MHZ | T0_DIV_1 | T0_ENABLED | T0_DOWN | T0_PERIODIC;

    /* enable timer0 interrupt */
    IRQEN = TIMER0_BIT;
    
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

void led_init(void)
{
    GP1DAT |=  (1 << 29); /* configure P1.5 as an output */
    GP1DAT &= ~(1 << 21); /* turn P1.5 off */
}

void led_toggle(void)
{
    GP1DAT ^= (1 << 21); /* toggle P1.5 */
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
