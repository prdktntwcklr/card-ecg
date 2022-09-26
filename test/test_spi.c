#ifdef TEST

#include "unity.h"

#define EXTERN 

#include "testable_mcu_registers.h"
#include "spi.h"

void setUp(void)
{
    SPIDIV = 0x1B; /* default value */
    GP0KEY1 = 0;
    GP0CON1 = 0;
    GP0KEY2 = 0;
}

void tearDown(void)
{
}

void test_spi_init_should_initializeSpiCorrectly(void)
{
    GP0CON1 = 0xFF;

    spi_init(5120000);
    TEST_ASSERT_EQUAL_INT(0, SPIDIV);
    TEST_ASSERT_EQUAL_HEX16(0x0007, GP0KEY1);
    TEST_ASSERT_EQUAL_HEX8(0xFD, GP0CON1);
    TEST_ASSERT_EQUAL_HEX16(0x0013, GP0KEY2);
}

#endif // TEST
