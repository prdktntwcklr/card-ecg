#include "main.h"
#include "aduc706x.h"
#include "superloop.h"
#include "timer.h"

void __attribute__((interrupt)) IRQHandler(void);

#ifndef TEST
int main(void)
#else
int testable_main(void)
#endif
{
    superloop_init();

    while(1)
    {
        while(superloop_run())
        {
            /* TODO: enter low power mode */
        }
    }

    return 0;
}

void IRQHandler(void)
{
    uint32_t irq = IRQSTA;

    if(irq & TIMER0_BIT)
    {
        timer_handle_interrupt();
        T0CLRI = 0;
    }
}
