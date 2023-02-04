#ifdef TEST

#include "unity.h"

#define EXTERN 

#include "testable_mcu_registers.h"
#include "display.h"
#include "display.c" /* hack to test static functions */
#include "mock_spi.h"
#include "mock_timer.h"
#include "my_assert_stub.h"

void setUp(void)
{
    GP0DAT = 0x0000ABCD; /* lower two bytes should not be affected */
}

void tearDown(void)
{
    display_deinit();
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

    TEST_ASSERT_FAIL_ASSERT(display_send_framebuffer(ptr));
}

void test_spi_send_data_should_throwErrorIfSpiIsNotInitialized(void)
{
    uint8_t data = 0xAA;

    TEST_ASSERT_FAIL_ASSERT(display_send_framebuffer(&data));
}

#endif // TEST
