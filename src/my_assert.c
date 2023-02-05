#include "my_assert.h"
#include "display.h"
#include "framebuffer.h"
#include "uart.h"
#include "uart_drv.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

void my_assert_failed(const char *file, int line)
{
    UNUSED(file);
    UNUSED(line);

    /* TODO: add filename and line number */
    uart_send_string("ASSERT failed!\r\n");

    /* wait for UART to finish sending */
    while(uart_drv_is_interrupt_enabled()) {}

    /* after sending message, disable all interrupts */
    IRQCLR = 0xFFFF;

    /* hang in while loop */
    while(1) {}
}
