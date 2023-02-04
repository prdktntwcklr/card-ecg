#ifdef TEST

#include "unity.h"

#define EXTERN

#include "main.h"
#include "mock_adc.h"
#include "mock_superloop.h"
#include "mock_timer.h"
#include "mock_uart.h"
#include "testable_mcu_registers.h"

void setUp(void)
{
    IRQSTA = 0x00000000;
    T0CLRI = 0xAA; /* dummy value to check if we write to T0CLRI */
}

void tearDown(void)
{
}

void test_main_should_callSuperloopInitAndThenRunMainLoop(void)
{
    superloop_init_Expect();

    superloop_run_ExpectAndReturn(true);
    superloop_run_ExpectAndReturn(true);
    superloop_run_ExpectAndReturn(false);

    TEST_ASSERT_EQUAL(0, testable_main());
}

void test_main_irq_should_handleTimer0InterruptCorrectly(void)
{
    IRQSTA = (1 << 3);
    T0CLRI = 0xAA;
    timer_handle_interrupt_Expect();
    testable_irq_handler();
    TEST_ASSERT_EQUAL_HEX8(0x00, T0CLRI);
}

void test_main_irq_should_handleUartInterruptCorrectly(void)
{
    IRQSTA = (1 << 11);
    uart_handle_interrupt_Expect();
    testable_irq_handler();
}

void test_main_irq_should_doNothingIfNoValidInterrupt(void)
{
    IRQSTA = (1 << 17); /* PWM bit */
    testable_irq_handler();
}

#endif // TEST
