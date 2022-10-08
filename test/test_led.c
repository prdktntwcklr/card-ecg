#ifdef TEST

#include "unity.h"

#define EXTERN 

#include "testable_mcu_registers.h"
#include "led.h"
#include "runtime_error_stub.h"

void setUp(void)
{
    GP1DAT = 0x0000ABCD; /* lower two bytes should not be affected */
}

void tearDown(void)
{
}

void test_led_init_should_setCorrectLedAsOutput(void)
{
    led_init();
    TEST_ASSERT_EQUAL_HEX32(0x2000ABCD, GP1DAT);
}

void test_led_init_should_turnLedOff(void)
{
    GP1DAT = 0xFFFFABCD;

    led_init();
    TEST_ASSERT_EQUAL_HEX32(0xFFDFABCD, GP1DAT);
}

void test_led_off_should_turnCorrectLedOff(void)
{
    GP1DAT = 0xFFFFABCD;
    
    led_init();
    led_off();
    TEST_ASSERT_EQUAL_HEX32(0xFFDFABCD, GP1DAT);
}

void test_led_on_should_turnCorrectLedOn(void)
{
    GP1DAT = 0xFF00ABCD;

    led_init();
    led_on();
    TEST_ASSERT_EQUAL_HEX32(0xFF20ABCD, GP1DAT);
}

void test_led_toggle_should_toggleCorrectLedOnOff(void)
{
    /* after init, led is off */
    led_init();

    /* toggle off to on */
    led_toggle();
    TEST_ASSERT_EQUAL_HEX32(0x2020ABCD, GP1DAT);

    /* toggle on to off */
    led_toggle();
    TEST_ASSERT_EQUAL_HEX32(0x2000ABCD, GP1DAT);    
}



#endif // TEST
