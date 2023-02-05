#ifdef TEST

#include "unity.h"

#define EXTERN

#include "testable_mcu_registers.h"

#include "my_assert_stub.h"
#include "ring_buffer.h"
#include "uart.c" /* hack to test static functions */
#include "uart.h"
#include "uart_drv.h"

void setUp(void)
{
    COMTX = 0;
}

void tearDown(void)
{
    uart_deinit();
}

void test_uart_send_string_should_throwErrorIfUartIsNotInitialized(void)
{
    TEST_ASSERT_FAIL_ASSERT(uart_send_string("Test!"));
}

void test_uart_send_string_should_putStringIntoBuffer(void)
{
    uart_init();
    uart_send_string("Hello!");

    /* first character gets placed into COMTX and interrupt is enabled */
    TEST_ASSERT_EQUAL('H', COMTX);
    TEST_ASSERT_TRUE(uart_drv_is_interrupt_enabled());

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

void test_uart_send_string_should_beHandledCorrectlyInInterrupt(void)
{
    uart_init();
    uart_send_string("World!");

    TEST_ASSERT_EQUAL('W', COMTX);
    TEST_ASSERT_TRUE(uart_drv_is_interrupt_enabled());

    COMIID0 = COMIID_TX_BUF_EMPTY;
    uart_handle_interrupt();
    TEST_ASSERT_EQUAL('o', COMTX);
    uart_handle_interrupt();
    TEST_ASSERT_EQUAL('r', COMTX);
    uart_handle_interrupt();
    TEST_ASSERT_EQUAL('l', COMTX);
    uart_handle_interrupt();
    TEST_ASSERT_EQUAL('d', COMTX);
    uart_handle_interrupt();
    TEST_ASSERT_EQUAL('!', COMTX);
    uart_handle_interrupt();

    TEST_ASSERT_FALSE(uart_drv_is_interrupt_enabled());
}

#endif // TEST
