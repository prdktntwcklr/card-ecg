#ifdef TEST

#include "unity.h"

#define EXTERN 

#include "testable_mcu_registers.h"
#include "uart.h"
#include "runtime_error_stub.h"

void setUp(void)
{
    GP1CON = 0;

    runtime_error_stub_reset();
}

void tearDown(void)
{
    uart_deinit();
}

void test_uart_init_should_initializeUartCorrectly(void)
{
    uart_init(9600);

    TEST_ASSERT_EQUAL_HEX32(0x00000010, GP1CON);
}

void test_uart_init_should_throwErrorIfBaudRateIsZero(void)
{
    uart_init(0);

    TEST_ASSERT_EQUAL_STRING("Uart baud rate cannot be zero!", runtime_error_stub_get_last_error());
}

#endif // TEST
