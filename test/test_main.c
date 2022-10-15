#ifdef TEST

#include "unity.h"

#define EXTERN 

#include "testable_mcu_registers.h"
#include "main.h"
#include "mock_timer.h"
#include "mock_superloop.h"

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
    IRQSTA = 0x00000008;
    timer_handle_interrupt_Expect();
    testable_irq_handler();
    TEST_ASSERT_EQUAL_HEX8(0x00, T0CLRI);

    IRQSTA = 0x00000049;
    T0CLRI = 0xAA;
    timer_handle_interrupt_Expect();
    testable_irq_handler();
    TEST_ASSERT_EQUAL_HEX8(0x00, T0CLRI);

    IRQSTA = 0x0000005C;
    T0CLRI = 0xAA;
    timer_handle_interrupt_Expect();
    testable_irq_handler();
    TEST_ASSERT_EQUAL_HEX8(0x00, T0CLRI);
}

void test_main_irq_should_notHandleTimer0InterruptIfNoTimer0Interrupt(void)
{
    testable_irq_handler();
    TEST_ASSERT_EQUAL_HEX8(0xAA, T0CLRI);

    IRQSTA = 0x00000037;
    T0CLRI = 0xAA;
    testable_irq_handler();
    TEST_ASSERT_EQUAL_HEX8(0xAA, T0CLRI);

    IRQSTA = 0x000000F7;
    T0CLRI = 0xAA;
    testable_irq_handler();
    TEST_ASSERT_EQUAL_HEX8(0xAA, T0CLRI);
}

#endif // TEST
