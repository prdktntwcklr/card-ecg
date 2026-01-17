#ifdef TEST

#include "unity.h"

#define EXTERN

#include "my_assert_stub.h"
#include "spi.h"
#include "testable_mcu_registers.h"

void setUp(void)
{
    SPIDIV = 0x1B; /* default value */
    GP0CON0 = 0;
    GP0KEY1 = 0;
    GP0CON1 = 0;
    GP0KEY2 = 0;
    SPICON = 0;
}

void tearDown(void)
{
    spi_deinit();
}

void test_spi_init_should_initializeSpiPinsCorrectly(void)
{
    /* check if correct bit is cleared */
    GP0CON1 = 0xFF;

    spi_init(5120000);
    TEST_ASSERT_EQUAL_HEX32(0x00001110, GP0CON0);
    TEST_ASSERT_EQUAL_UINT8(0, SPIDIV);
    TEST_ASSERT_EQUAL_HEX16(0x0007, GP0KEY1);
    TEST_ASSERT_EQUAL_HEX8(0xFD, GP0CON1);
    TEST_ASSERT_EQUAL_HEX16(0x0013, GP0KEY2);
}

void test_spi_init_should_initializeSpiPeripheralCorrectly(void)
{
    spi_init(5120000);

    TEST_ASSERT_EQUAL_HEX16(0x0ACF, SPICON);
}

void test_spi_init_should_notAcceptBitRateOfZero(void)
{
    TEST_ASSERT_FAIL_ASSERT(spi_init(0));
}

void test_spi_send_data_should_throwErrorIfSpiIsNotInitialized(void)
{
    TEST_ASSERT_FAIL_ASSERT(spi_send_data(0xAA));
}

#endif // TEST
