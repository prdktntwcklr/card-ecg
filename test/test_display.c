#ifdef TEST

#include "unity.h"

#define EXTERN 

#include "testable_mcu_registers.h"
#include "display.h"
#include "display.c"
#include "mock_spi.h"
#include "mock_timer.h"
#include "runtime_error_stub.h"

void setUp(void)
{
    GP0DAT = 0x0000ABCD; /* lower two bytes should not be affected */

    runtime_error_stub_reset();
}

void tearDown(void)
{
}

/* this test must run before any calls to display_init() */
void test_spi_send_data_should_throwErrorIfSpiIsNotInitialized(void)
{
    uint8_t data = 0xAA;

    display_send_framebuffer(&data);

    TEST_ASSERT_EQUAL_STRING("Display is not initialized!", runtime_error_stub_get_last_error());
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

void test_display_send_framebuffer_should_throwErrorIfNullPointerReceived(void)
{
    uint8_t *ptr = NULL;

    display_send_framebuffer(ptr);

    TEST_ASSERT_EQUAL_STRING("Null pointer received!", runtime_error_stub_get_last_error());
}

#endif // TEST
