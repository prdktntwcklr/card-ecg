#ifdef TEST

#include "unity.h"

#include <stdbool.h>

#include "framebuffer.h"
#include "framebuffer.c"
#include "runtime_error_stub.h"

void setUp(void)
{
}

void tearDown(void)
{
    runtime_error_stub_reset();
}

void test_framebuffer_clear_should_clearTheFramebuffer(void)
{
    uint64_t fakeFramebuffer[FRAMEBUFFER_ELEMENTS] = {0xAAAAAAAAAAAAAAAA};

    uint8_t* framebuffer = (uint8_t*) fakeFramebuffer;

    framebuffer_clear(framebuffer);

    for(uint8_t i = 0; i < FRAMEBUFFER_ELEMENTS; i++)
    {
        TEST_ASSERT_EQUAL_HEX64(0x0000000000000000, fakeFramebuffer[i]);
    }
}

void test_framebuffer_init_should_returnPointerToClearedFramebuffer(void)
{
    uint8_t* framebuffer = framebuffer_init();

    for(uint16_t i = 0; i < FRAMEBUFFER_ELEMENTS * 8; i++)
    {
        TEST_ASSERT_EQUAL_HEX8(0x00, framebuffer[i]);
    }    
}

void test_framebuffer_change_pixel_should_throwErrorIfOutsideOfLimits(void)
{
    uint8_t* framebuffer = framebuffer_init();

    framebuffer_change_pixel(framebuffer, 0, 200, true);

    TEST_ASSERT_EQUAL_STRING("Outside of framebuffer limits!", runtime_error_stub_get_last_error());
}

#endif // TEST
