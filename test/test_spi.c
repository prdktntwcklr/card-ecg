#ifdef TEST

#include "unity.h"

#define EXTERN 

#include "testable_mcu_registers.h"
#include "spi.h"
#include "runtime_error_stub.h"

void setUp(void)
{
    SPIDIV = 0x1B; /* default value */
    GP0CON0 = 0;
    GP0KEY1 = 0;
    GP0CON1 = 0;
    GP0KEY2 = 0;
    SPICON = 0;

    runtime_error_stub_reset();
}

void tearDown(void)
{
}

/* this test must run before any calls to spi_init() */
void test_spi_send_data_should_throwErrorIfSpiIsNotInitialized(void)
{
    spi_send_data(0xAA);

    TEST_ASSERT_EQUAL_STRING("Spi is not initialized!", runtime_error_stub_get_last_error());
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

    TEST_ASSERT_EQUAL_STRING("No Error!", runtime_error_stub_get_last_error());
}

void test_spi_init_should_initializeSpiPeripheralCorrectly(void)
{
    spi_init(5120000);

    TEST_ASSERT_EQUAL_HEX16(0x0ACF, SPICON);

    TEST_ASSERT_EQUAL_STRING("No Error!", runtime_error_stub_get_last_error());
}

void test_spi_init_should_notAcceptBitRateOfZero(void)
{
    spi_init(0);

    TEST_ASSERT_EQUAL_STRING("Spi bit rate cannot be zero!", runtime_error_stub_get_last_error());

    /* make sure rest of function does not run after runtime assert fails */
    TEST_ASSERT_EQUAL_HEX32(0x00000000, GP0CON0);
}

#endif // TEST
