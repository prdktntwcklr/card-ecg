#include "my_assert.h"
#include "display.h"
#include "framebuffer.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

void my_assert_failed(const char *file, int line)
{
    /* TODO: output string to screen or uart */
    UNUSED(file);
    UNUSED(line);

    /* after sending message, disable all interrupts */
    IRQCLR = 0xFFFF;

    /* hang in while loop */
    while(1) {}
}
