#include "my_assert.h"
#include "display.h"
#include "framebuffer.h"
#include "my_printf.h"
#include "uart.h"
#include "uart_drv.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

/* cppcheck-suppress unusedFunction */
void my_assert_failed(const char *file, int line)
{
    UNUSED(file);
    UNUSED(line);

    /* TODO: add filename and line number */
    MY_PRINTF("ASSERT in %s:%d\r\n", file, line);

    /* wait for UART to finish sending */
    while(uart_drv_is_interrupt_enabled())
    {
    }

    /* after sending message, disable all interrupts */
    IRQCLR = 0xFFFF;

    /* hang in while loop */
    while(1)
    {
    }
}
/*** end of file ***/
