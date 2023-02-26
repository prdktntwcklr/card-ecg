#ifdef TEST

#include "unity.h"

#define EXTERN

#include "testable_mcu_registers.h"
#include "uart_drv.h"

void setUp(void)
{
    GP1CON = 0;
    COMCON0 = 0;
    COMDIV0 = 0;
    COMDIV1 = 0;
    COMDIV2 = 0;
    COMTX = 0;
    COMIEN0 = 0;
    COMIID0 = 0;
    IRQEN = 0;
}

void tearDown(void)
{
}

void test_uart_drv_init_should_initializeUartCorrectly(void)
{
    uart_drv_init();

    TEST_ASSERT_EQUAL_HEX32(0x00000010, GP1CON);

    TEST_ASSERT_EQUAL_HEX8(0x21, COMDIV0);
    TEST_ASSERT_EQUAL_HEX8(0x00, COMDIV1);
    TEST_ASSERT_EQUAL_HEX16(0x0815, COMDIV2);

    TEST_ASSERT_EQUAL_HEX8(0x03, COMCON0);

    TEST_ASSERT_EQUAL_HEX32((1 << 11), IRQEN);
}

void test_uart_drv_is_interrupt_enabled_should_returnCorrectValues(void)
{
    TEST_ASSERT_FALSE(uart_drv_is_interrupt_enabled());

    COMIEN0 |= (1 << 0);
    TEST_ASSERT_FALSE(uart_drv_is_interrupt_enabled());

    COMIEN0 |= (1 << 1);
    TEST_ASSERT_TRUE(uart_drv_is_interrupt_enabled());

    COMIEN0 |= (1 << 2);
    TEST_ASSERT_TRUE(uart_drv_is_interrupt_enabled());

    COMIEN0 &= ~(1 << 1);
    TEST_ASSERT_FALSE(uart_drv_is_interrupt_enabled());
}

void test_uart_drv_enable_interrupt_should_enableInterrupt(void)
{
    TEST_ASSERT_FALSE(uart_drv_is_interrupt_enabled());
    uart_drv_enable_interrupt();
    TEST_ASSERT_TRUE(uart_drv_is_interrupt_enabled());
}

void test_uart_drv_disable_interrupt_should_disableInterrupt(void)
{
    uart_drv_enable_interrupt();
    TEST_ASSERT_TRUE(uart_drv_is_interrupt_enabled());
    uart_drv_disable_interrupt();
    TEST_ASSERT_FALSE(uart_drv_is_interrupt_enabled());
}

void test_is_tx_buf_empty_interrupt_shouldReturnCorrectly(void)
{
    COMIID0 = 0;
    TEST_ASSERT_FALSE(is_tx_buf_empty_interrupt());

    COMIID0 = 0x02;
    TEST_ASSERT_TRUE(is_tx_buf_empty_interrupt());
}

#endif // TEST
