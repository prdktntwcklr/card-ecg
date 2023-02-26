#include "main.h"
#include "adc.h"
#include "superloop.h"
#include "timer.h"
#include "uart.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

#ifndef TEST
__attribute__((interrupt)) void IRQHandler(void);
#endif

#ifndef TEST
int main(void)
#else
/* cppcheck-suppress unusedFunction */
int testable_main(void)
#endif
{
    superloop_init();

    while(superloop_run())
    {
        /* TODO: enter low power mode */
    }

    return 0;
}

#ifndef TEST
void IRQHandler(void)
#else
/* cppcheck-suppress unusedFunction */
void testable_irq_handler(void)
#endif
{
    uint32_t irq_status = IRQSTA;

    if((irq_status & TIMER0_BIT) == TIMER0_BIT)
    {
        timer_handle_interrupt();
        T0CLRI = 0; /* clear Timer0 interrupt */
    }
    else if((irq_status & UART_BIT) == UART_BIT)
    {
        uart_handle_interrupt();
    }
    else if((irq_status & ADC_BIT) == ADC_BIT)
    {
        adc_handle_interrupt();
    }
}
/*** end of file ***/
