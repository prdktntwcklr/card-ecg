#ifdef TEST

#include "unity.h"

#include <stdbool.h>

#include "framebuffer.h"
#include "framebuffer.c" /* hack to test static functions */
#include "font.h"
#include "mock_image.h"
#include "runtime_error_stub.h"

void setUp(void)
{
}

void tearDown(void)
{
    framebuffer_deinit();
    runtime_error_stub_reset();
}

void test_framebuffer_init_should_throwErrorIfCalledTwice(void)
{
    framebuffer_init();
    framebuffer_init();

    TEST_ASSERT_EQUAL_STRING("Framebuffer is already initialized!", runtime_error_stub_get_last_error());
}

void test_framebuffer_get_should_returnFramebufferHandlerIfFramebufferIsInitialized(void)
{
    framebuffer_init();
    fb_handle_t framebuffer = framebuffer_get();

    TEST_ASSERT_EQUAL_STRING("No Error!", runtime_error_stub_get_last_error());
}

void test_framebuffer_clear_should_clearTheFramebuffer(void)
{
    uint64_t fakeFramebuffer[FRAMEBUFFER_ELEMENTS] = {0xAAAAAAAAAAAAAAAA};

    fb_handle_t framebuffer = (fb_handle_t) fakeFramebuffer;

    framebuffer_clear(framebuffer);

    for(uint8_t i = 0; i < FRAMEBUFFER_ELEMENTS; i++)
    {
        TEST_ASSERT_EQUAL_HEX64(0x0000000000000000, fakeFramebuffer[i]);
    }
}

void test_framebuffer_get_after_init_should_returnPointerToClearedFramebuffer(void)
{
    framebuffer_init();
    fb_handle_t framebuffer = framebuffer_get();

    for(uint16_t i = 0; i < FRAMEBUFFER_ELEMENTS * 8; i++)
    {
        TEST_ASSERT_EQUAL_HEX8(0x00, framebuffer[i]);
    }    
}

void test_framebuffer_change_pixel_should_throwErrorIfOutsideOfLimits(void)
{
    framebuffer_init();
    fb_handle_t framebuffer = framebuffer_get();

    framebuffer_change_pixel(framebuffer, 0, 200, true);

    TEST_ASSERT_EQUAL_STRING("Outside of framebuffer limits!", runtime_error_stub_get_last_error());
}

void test_end_of_string_reached_should_returnCorrectValues(void)
{
    TEST_ASSERT_FALSE(end_of_string_reached('a'));
    TEST_ASSERT_FALSE(end_of_string_reached('G'));
    TEST_ASSERT_FALSE(end_of_string_reached('?'));
    TEST_ASSERT_TRUE(end_of_string_reached('\0'));
    TEST_ASSERT_TRUE(end_of_string_reached(0));
    TEST_ASSERT_FALSE(end_of_string_reached('#'));
    TEST_ASSERT_FALSE(end_of_string_reached('3'));
}

void test_end_of_line_reached_should_returnCorrectValues(void)
{
    TEST_ASSERT_FALSE(end_of_line_reached(0));
    TEST_ASSERT_FALSE(end_of_line_reached(54));
    TEST_ASSERT_FALSE(end_of_line_reached(99));
    TEST_ASSERT_FALSE(end_of_line_reached(122));
    TEST_ASSERT_TRUE(end_of_line_reached(123));
    TEST_ASSERT_TRUE(end_of_line_reached(-5));
}

void test_bottom_of_framebuffer_reached_should_returnCorrectValues(void)
{
    TEST_ASSERT_FALSE(bottom_of_framebuffer_reached(0));
    TEST_ASSERT_FALSE(bottom_of_framebuffer_reached(54));
    TEST_ASSERT_TRUE(bottom_of_framebuffer_reached(99));
    TEST_ASSERT_TRUE(bottom_of_framebuffer_reached(122));
    TEST_ASSERT_TRUE(bottom_of_framebuffer_reached(123));
    TEST_ASSERT_TRUE(bottom_of_framebuffer_reached(-5));
}

void test_whitespace_at_line_beginning_should_returnCorrectValues(void)
{
    TEST_ASSERT_TRUE(whitespace_at_line_beginning(0, ' '));
    TEST_ASSERT_FALSE(whitespace_at_line_beginning(1, ' '));
    TEST_ASSERT_FALSE(whitespace_at_line_beginning(128, ' '));
    TEST_ASSERT_FALSE(whitespace_at_line_beginning(0, 'a'));
    TEST_ASSERT_FALSE(whitespace_at_line_beginning(0, '?'));
    TEST_ASSERT_FALSE(whitespace_at_line_beginning(0, 'X'));
}

void test_framebuffer_get_should_throwErrorIfFramebufferIsNotInitialized(void)
{
    fb_handle_t framebuffer = framebuffer_get();

    TEST_ASSERT_EQUAL_STRING("Framebuffer must be initialized first!", runtime_error_stub_get_last_error());
}

#endif // TEST
