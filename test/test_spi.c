#ifdef TEST

#include "unity.h"

#define EXTERN 

#include "testable_mcu_registers.h"
#include "spi.h"

void setUp(void)
{
    SPIDIV = 0x1B; /* default value */
}

void tearDown(void)
{
}

void test_spi_init_should_initializeSpiCorrectly(void)
{
    spi_init(5120000);
    TEST_ASSERT_EQUAL_INT(0, SPIDIV);
}

#endif // TEST
