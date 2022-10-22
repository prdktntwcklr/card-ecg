#ifdef TEST

#include "unity.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "framebuffer.h"
#include "framebuffer.c" /* hack to test static functions */
#include "font.h"
#include "image.h"
#include "runtime_error_stub.h"

void setUp(void)
{
}

void tearDown(void)
{
    framebuffer_deinit();
    runtime_error_stub_reset();
}

/*
 * @brief Dumps the framebuffer to the screen.
 *
 * @note  Could be used for comparing expected to actual output.
 */
static void dump_framebuffer(fb_handle_t framebuffer)
{
    for(uint8_t y = 0; y < FRAMEBUFFER_HEIGHT; y++)
    {
        for(uint8_t x = 0; x < FRAMEBUFFER_WIDTH; x++)
        {
            image_get_pixel((uint8_t*) framebuffer, x, y) ? printf("#") : printf(".");
        }
        
        /* end of a line reached, switch to next line */
        printf("\n");
    }        
}

/*
 * @brief Checks if a line in the framebuffer matches the expectation.
 */
static void check_framebuffer_line(fb_handle_t framebuffer, const uint8_t line, const char *expected)
{
    /* open file for writing */
    FILE* tmp = fopen("tmp.txt", "w");

    if(!tmp)
    {
        fprintf(stderr, "Failed to create tmpfile: %s (errno = %d)\n", strerror(errno), errno);
        TEST_FAIL();
    }

    for(uint8_t x = 0; x < strlen(expected); x++)
    {
        image_get_pixel((uint8_t*) framebuffer, x, line) ? fprintf(tmp, "#") : fprintf(tmp, ".");
    }

    fclose(tmp);

    /* open file for reading */
    tmp = fopen("tmp.txt", "r");

    if(!tmp)
    {
        fprintf(stderr, "Failed to open tmpfile: %s (errno = %d)\n", strerror(errno), errno);
        TEST_FAIL();
    }

    /* copy file contents to buffer */
    const int length = strlen(expected) + 1;
    char actual[length];

    fgets(actual, length, tmp);
    fclose(tmp);

    /* delete file */
    int err_no = remove("tmp.txt");

    if(err_no != 0)
    {
        fprintf(stderr, "Failed to delete tmpfile: %s (errno = %d)\n", strerror(errno), errno);
        TEST_FAIL();        
    }

    TEST_ASSERT_EQUAL_STRING(expected, actual);
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

void test_framebuffer_get_should_throwErrorIfFramebufferIsNotInitialized(void)
{
    fb_handle_t framebuffer = framebuffer_get();

    TEST_ASSERT_EQUAL_STRING("Framebuffer must be initialized first!", runtime_error_stub_get_last_error());
}

void test_framebuffer_get_should_returnPointerToClearedFramebufferAfterInit(void)
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

void test_framebuffer_change_pixel_should_changePixelCorrectly(void)
{
    framebuffer_init();
    fb_handle_t framebuffer = framebuffer_get();

    framebuffer_change_pixel(framebuffer, 0, 0, true);
    framebuffer_change_pixel(framebuffer, 3, 3, true);
    framebuffer_change_pixel(framebuffer, 6, 29, false);

    TEST_ASSERT_TRUE(image_get_pixel((uint8_t*) framebuffer, 0, 0));
    TEST_ASSERT_FALSE(image_get_pixel((uint8_t*) framebuffer, 0, 1)) ;
    TEST_ASSERT_TRUE(image_get_pixel((uint8_t*) framebuffer, 3, 3)) ;
    TEST_ASSERT_FALSE(image_get_pixel((uint8_t*) framebuffer, 4, 5)) ;
    TEST_ASSERT_FALSE(image_get_pixel((uint8_t*) framebuffer, 6, 29)) ;
}

void test_framebuffer_draw_symbol_should_drawSymbolCorrectly(void)
{
    framebuffer_init();
    fb_handle_t framebuffer = framebuffer_get();

    framebuffer_draw_symbol(framebuffer, 0, 0, 'A');

    check_framebuffer_line(framebuffer, 0, "...#...");
    check_framebuffer_line(framebuffer, 1, "..#.#..");
    check_framebuffer_line(framebuffer, 2, ".#...#.");
    check_framebuffer_line(framebuffer, 3, ".#...#.");
    check_framebuffer_line(framebuffer, 4, ".#####.");
    check_framebuffer_line(framebuffer, 5, ".#...#.");
    check_framebuffer_line(framebuffer, 6, ".#...#.");
    check_framebuffer_line(framebuffer, 7, ".......");
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

void test_framebuffer_draw_string_should_drawStringCorrectly(void)
{
    framebuffer_init();
    fb_handle_t framebuffer = framebuffer_get();

    framebuffer_draw_string(framebuffer, 0, 0, "Test.");

    check_framebuffer_line(framebuffer, 0, ".#####.................#.........");
    check_framebuffer_line(framebuffer, 1, "...#...................#.........");
    check_framebuffer_line(framebuffer, 2, "...#.....###....###...###........");
    check_framebuffer_line(framebuffer, 3, "...#....#...#..#.......#.........");
    check_framebuffer_line(framebuffer, 4, "...#....#####...###....#.........");
    check_framebuffer_line(framebuffer, 5, "...#....#..........#...#..#...##.");
    check_framebuffer_line(framebuffer, 6, "...#.....###...####.....##....##.");
    check_framebuffer_line(framebuffer, 7, ".................................");
}

#endif // TEST
