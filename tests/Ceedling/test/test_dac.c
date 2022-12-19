#ifdef TEST

#include "unity.h"

#define EXTERN 

#include "testable_mcu_registers.h"
#include "dac.h"
#include "dac.c" /* hack to test static functions */
#include "runtime_error_stub.h"

void setUp(void)
{
    DAC0CON = 0;
    DAC0DAT = 0;

    runtime_error_stub_reset();
}

void tearDown(void)
{
    dac_deinit();
}

void test_dac_init_should_initializeDacCorrectly(void)
{
    dac_init();

    TEST_ASSERT_EQUAL_HEX16(0x0010, DAC0CON);
}

void test_dac_set_should_throwErrorIfDacIsNotInitialized(void)
{
    dac_set(0xAA);

    TEST_ASSERT_EQUAL_STRING("Dac is not initialized!", runtime_error_stub_get_last_error());
}

void test_dac_set_should_throwErrorIfValueIsTooHigh(void)
{
    dac_init();
    dac_set(0x1FFF);

    TEST_ASSERT_EQUAL_STRING("Dac value > 0x0FFF!", runtime_error_stub_get_last_error());
}

void test_dac_set_should_setDacToCorrectValue(void)
{
    dac_init();

    dac_set(0x00AA);
    TEST_ASSERT_EQUAL_HEX32(0x00AA0000, DAC0DAT);

    dac_set(0x0FFF);
    TEST_ASSERT_EQUAL_HEX32(0x0FFF0000, DAC0DAT);

    dac_set(0x0001);
    TEST_ASSERT_EQUAL_HEX32(0x00010000, DAC0DAT);
}

#endif // TEST