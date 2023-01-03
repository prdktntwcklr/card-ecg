#ifdef TEST

#include "unity.h"

#define EXTERN 

#include "testable_mcu_registers.h"
#include "uart.h"
#include "uart.c" /* hack to test static functions */
#include "my_assert_stub.h"

void setUp(void)
{
    GP1CON = 0;
    COMCON0 = 0;
    COMDIV0 = 0;
    COMDIV1 = 0;
    COMDIV2 = 0;
    COMTX = 0;
}

void tearDown(void)
{
    uart_deinit();
}

void test_uart_init_should_initializeUartCorrectly(void)
{
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

void test_uart_send_string_should_putDataIntoTxRegister(void)
{
    COMSTA0 |= TX_BUF_EMPTY; /* set buf empty bit so that we don't hang in while loop */

    uart_init();

    uart_send_string("H");
    TEST_ASSERT_EQUAL_HEX8('H', COMTX);

    uart_send_string("He");
    TEST_ASSERT_EQUAL_HEX8('e', COMTX);

    uart_send_string("Hello");
    TEST_ASSERT_EQUAL_HEX8('o', COMTX);
}

#endif // TEST
