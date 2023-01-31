#include "framebuffer.h"
#include "font.h"
#include "image.h"
#include "my_assert.h"

#define FRAMEBUFFER_ELEMENTS ((FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT)/(8UL * 8UL))

#define ASCII_OFFSET          (32U)
#define MAX_STRING_LENGTH    (100U)

static fb_handle_t framebuffer_ptr = 0;
static uint64_t framebuffer_array[FRAMEBUFFER_ELEMENTS];

STATIC_ASSERT(sizeof(framebuffer_array)
                  == (128UL * sizeof(framebuffer_array[0])),
              framebuffer_should_contain_128_elements);

/* helper functions declarations */
static bool end_of_string_reached(char next_symbol);
static bool end_of_line_reached(uint8_t next_x_pos);
static bool bottom_of_framebuffer_reached(uint8_t next_y_pos);
static bool whitespace_at_line_beginning(uint8_t next_x_pos, char next_symbol);

#ifdef TEST
static void framebuffer_deinit(void);
#endif

/**
 * @brief Initializes the framebuffer and clears it.
 */
void framebuffer_init(void)
{
    if(!framebuffer_ptr)
    {
        framebuffer_ptr = (fb_handle_t) framebuffer_array;

        framebuffer_clear(framebuffer_ptr);
    }
}

#ifdef TEST
/**
 * @brief Denitializes the framebuffer.
 *
 * @note  Helper function for unit testing.
 */
/* cppcheck-suppress unusedFunction */
static void framebuffer_deinit(void)
{
    framebuffer_ptr = 0;
}
#endif

/**
 * @brief Clears the whole framebuffer.
 *
 * @note  Passing the framebuffer handle as a parameter allows unit tests
 *        to inject a fake framebuffer here.
 */
void framebuffer_clear(fb_handle_t framebuffer)
{
    MY_ASSERT(framebuffer);

    for (uint8_t i = 0; i < (uint8_t) FRAMEBUFFER_ELEMENTS; i++)
    {
        framebuffer[i] = 0;
    }
}

/**
 * @brief Returns the framebuffer.
 */
/* cppcheck-suppress unusedFunction */
fb_handle_t framebuffer_get(void)
{
    /* framebuffer must be initialized first */
    MY_ASSERT(framebuffer_ptr);

    return framebuffer_ptr;
}

/**
 * @brief Changes (sets or resets) a single pixel of the framebuffer.
 *
 * @note  Passing the framebuffer handle as a parameter allows unit tests
 *        to inject a fake framebuffer here.
 */
void framebuffer_change_pixel(fb_handle_t framebuffer, uint8_t x, uint8_t y,
                              bool set)
{
    MY_ASSERT(framebuffer);
    MY_ASSERT(x < FRAMEBUFFER_WIDTH && y < FRAMEBUFFER_HEIGHT);

    if(set)
    {
        framebuffer[x + ((y & 0xF8) << 4)] |= 1 << (y & 7);
    }
    else
    {
        framebuffer[x + ((y & 0xF8) << 4)] &= ~(1 << (y & 7));
    }
}

/**
 * @brief Draws a single symbol (character) to the framebuffer.
 *
 * @note  Passing the framebuffer handle as a parameter allows unit tests
 *        to inject a fake framebuffer here.
 */
void framebuffer_draw_symbol(fb_handle_t framebuffer, uint8_t x, uint8_t y,
                             uint8_t symbol)
{
    uint16_t ascii_symbol = (symbol - ASCII_OFFSET) * FONT_WIDTH;
    
    for (uint8_t dx = 0; dx < FONT_WIDTH; dx++)
    {
        for (uint32_t dy = 0; dy < FONT_HEIGHT; dy++)
        {
            framebuffer_change_pixel(
                framebuffer, dx + x, dy + y,
                image_get_pixel(&ssd1306xled_font6x8[ascii_symbol], dx, dy));
        }
    }
}

/**
 * @brief Checks if we have reached the end of the string.
 */
static bool end_of_string_reached(char next_symbol)
{
    return (next_symbol == 0);
}

/**
 * @brief Checks if the x position for the next symbol goes
 *        beyond the end of the line.
 */
static bool end_of_line_reached(uint8_t next_x_pos)
{
    return ((next_x_pos + FONT_WIDTH) > FRAMEBUFFER_WIDTH);
}

/**
 * @brief Checks if the y position for the next symbol goes
 *        beyond the edge of the framebuffer.
 */
static bool bottom_of_framebuffer_reached(uint8_t next_y_pos)
{
    return ((next_y_pos + FONT_HEIGHT) > FRAMEBUFFER_HEIGHT);
}

/**
 * @brief Checks if the next symbol is a whitespace at the beginning of a line.
 */
static bool whitespace_at_line_beginning(uint8_t next_x_pos, char next_symbol)
{
    return ((next_x_pos == 0) && (next_symbol == ' '));
}

/**
 * @brief Outputs a string to the framebuffer.
 *
 * @note  Passing the framebuffer handle as a parameter allows unit tests
 *        to inject a fake framebuffer here.
 */
/* cppcheck-suppress unusedFunction */
void framebuffer_draw_string(fb_handle_t framebuffer, uint8_t x, uint8_t y,
                             const char *string)
{
    /* #lizard forgives (exclude from code complexity check) */

    MY_ASSERT(string);

    /* initialize variables to start position of string */
    uint8_t next_x_pos = x;
    uint8_t next_y_pos = y;

    /* print every character of string */
    for(uint8_t i = 0; i < MAX_STRING_LENGTH; i++)
    {
        char next_symbol = string[i];

        if(end_of_string_reached(next_symbol))
        {
            break;
        }

        if(end_of_line_reached(next_x_pos))
        {
            /* switch to next line */
            next_x_pos  = 0; /* lines start at zero x position */
            next_y_pos += FONT_HEIGHT;
        }

        if(bottom_of_framebuffer_reached(next_y_pos))
        {
            break;
        }

        if(!whitespace_at_line_beginning(next_x_pos, next_symbol))
        {
            framebuffer_draw_symbol(framebuffer, next_x_pos, next_y_pos,
                                    next_symbol);
            next_x_pos += (FONT_WIDTH + 1);
        }
    }
}

/**
 * @brief Draws an image to the framebuffer.
 *
 * @note  Passing the framebuffer handle as a parameter allows unit tests
 *        to inject a fake framebuffer here.
 */
/* cppcheck-suppress unusedFunction */
void framebuffer_draw_image(fb_handle_t framebuffer, uint8_t *image)
{
    for (uint8_t x_pos = 0; x_pos < FRAMEBUFFER_WIDTH; x_pos++)
    {
        for (uint32_t y_pos = 0; y_pos < FRAMEBUFFER_HEIGHT; y_pos++)
        {
            framebuffer_change_pixel(framebuffer, x_pos, y_pos,
                                     image_get_pixel(image, x_pos, y_pos));
        }
    }
}
