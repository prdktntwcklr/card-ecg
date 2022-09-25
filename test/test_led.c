#ifdef TEST

#include "unity.h"

#define EXTERN 

#include "testable_mcu_registers.h"
#include "led.h"

void setUp(void)
{
    GP1DAT = 0x00000000;
}

void tearDown(void)
{
}

void test_led_init_should_setCorrectLedAsOutputAndTurnLedOff(void)
{
    led_init();
    TEST_ASSERT_EQUAL_HEX32(0x20000000, GP1DAT);
}

void test_led_off_should_turnCorrectLedOff(void)
{
    GP1DAT = 0xFFFF0000;
    led_off();
    TEST_ASSERT_EQUAL_HEX32(0xFFDF0000, GP1DAT);
}

void test_led_on_should_turnCorrectLedOn(void)
{
    led_init();
    led_on();
    TEST_ASSERT_EQUAL_HEX32(0x20200000, GP1DAT);
}

void test_led_toggle_should_toggleCorrectLedOnOff(void)
{
    led_init();
    TEST_ASSERT_EQUAL_HEX32(0x20000000, GP1DAT);
    led_toggle();
    TEST_ASSERT_EQUAL_HEX32(0x20200000, GP1DAT);
    led_toggle();
    TEST_ASSERT_EQUAL_HEX32(0x20000000, GP1DAT);    
}

#endif // TEST
