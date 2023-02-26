#ifdef TEST

#include "unity.h"

#define EXTERN

#include "display_drv.h"
#include "testable_mcu_registers.h"

void setUp(void)
{
    GP0DAT = 0x0000ABCD; /* lower two bytes should not be affected */
}

void tearDown(void)
{
}

void test_display_cs_on_should_setCorrectPin(void)
{
    display_cs_on();
    TEST_ASSERT_EQUAL_HEX32(0x0001ABCD, GP0DAT);
}

void test_display_cs_off_should_clearCorrectPin(void)
{
    GP0DAT = 0x00FFABCD;

    display_cs_off();
    TEST_ASSERT_EQUAL_HEX32(0x00FEABCD, GP0DAT);
}

void test_display_reset_on_should_setCorrectPin(void)
{
    display_reset_on();
    TEST_ASSERT_EQUAL_HEX32(0x0004ABCD, GP0DAT);
}

void test_display_reset_off_should_clearCorrectPin(void)
{
    GP0DAT = 0x00FFABCD;

    display_reset_off();
    TEST_ASSERT_EQUAL_HEX32(0x00FBABCD, GP0DAT);
}

void test_display_dc_on_should_setCorrectPin(void)
{
    display_dc_on();
    TEST_ASSERT_EQUAL_HEX32(0x0010ABCD, GP0DAT);
}

void test_display_dc_off_should_clearCorrectPin(void)
{
    GP0DAT = 0x00FFABCD;

    display_dc_off();
    TEST_ASSERT_EQUAL_HEX32(0x00EFABCD, GP0DAT);
}

void test_display_gpio_init_should_setCorrectPins(void)
{
    GP0DAT = 0x00FFABCD;

    display_gpio_init();

    TEST_ASSERT_EQUAL_HEX32(0x15EAABCD, GP0DAT);
}

#endif // TEST
