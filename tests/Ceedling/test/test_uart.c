#ifdef TEST

#include "unity.h"

#define EXTERN

#include "my_assert_stub.h"
#include "ring_buffer.h"
#include "testable_mcu_registers.h"
#include "uart.c" /* hack to test static functions */
#include "uart.h"

void setUp(void)
{
    GP1CON = 0;
    COMCON0 = 0;
    COMDIV0 = 0;
    COMDIV1 = 0;
    COMDIV2 = 0;
    COMTX = 0;
    COMIEN0 = 0;
}

void tearDown(void)
{
    uart_deinit();
}

void test_uart_init_should_initializeUartCorrectly(void)
{
    // ring_buffer_reset_Expect();
    uart_init();

    TEST_ASSERT_EQUAL_HEX32(0x00000010, GP1CON);

    TEST_ASSERT_EQUAL_HEX8(0x21, COMDIV0);
    TEST_ASSERT_EQUAL_HEX8(0x00, COMDIV1);
    TEST_ASSERT_EQUAL_HEX16(0x0815, COMDIV2);

    TEST_ASSERT_EQUAL_HEX8(0x03, COMCON0);
}

void test_uart_send_string_should_throwErrorIfUartIsNotInitialized(void)
{
    TEST_ASSERT_FAIL_ASSERT(uart_send_string("Test!"));
}

void test_uart_is_interrupt_enabled_should_returnCorrectValues(void)
{
    TEST_ASSERT_FALSE(uart_is_interrupt_enabled());

    COMIEN0 |= (1 << 0);
    TEST_ASSERT_FALSE(uart_is_interrupt_enabled());

    COMIEN0 |= (1 << 1);
    TEST_ASSERT_TRUE(uart_is_interrupt_enabled());

    COMIEN0 |= (1 << 2);
    TEST_ASSERT_TRUE(uart_is_interrupt_enabled());

    COMIEN0 &= ~(1 << 1);
    TEST_ASSERT_FALSE(uart_is_interrupt_enabled());
}

void test_uart_enable_interrupt_should_enableInterrupt(void)
{
    TEST_ASSERT_FALSE(uart_is_interrupt_enabled());
    uart_enable_interrupt();
    TEST_ASSERT_TRUE(uart_is_interrupt_enabled());
}

void test_uart_disable_interrupt_should_disableInterrupt(void)
{
    uart_enable_interrupt();
    TEST_ASSERT_TRUE(uart_is_interrupt_enabled());
    uart_disable_interrupt();
    TEST_ASSERT_FALSE(uart_is_interrupt_enabled());
}

void test_uart_send_string_should_putStringIntoBuffer(void)
{
    uart_init();
    uart_send_string("Hello!");

    /* first character gets placed into COMTX and interrupt is enabled */
    TEST_ASSERT_EQUAL('H', COMTX);
    TEST_ASSERT_TRUE(uart_is_interrupt_enabled());

    /* check if rest of string is also there */
    char symbol;
    TEST_ASSERT_TRUE(ring_buffer_get(&symbol));
    TEST_ASSERT_EQUAL('e', symbol);
    TEST_ASSERT_TRUE(ring_buffer_get(&symbol));
    TEST_ASSERT_EQUAL('l', symbol);
    TEST_ASSERT_TRUE(ring_buffer_get(&symbol));
    TEST_ASSERT_EQUAL('l', symbol);
    TEST_ASSERT_TRUE(ring_buffer_get(&symbol));
    TEST_ASSERT_EQUAL('o', symbol);
    TEST_ASSERT_TRUE(ring_buffer_get(&symbol));
    TEST_ASSERT_EQUAL('!', symbol);

    /* ring buffer should be empty now */
    TEST_ASSERT_TRUE(ring_buffer_is_empty());
}

#endif // TEST
