#include "framebuffer.h"
#include "font.h"
#include "image.h"
#include "runtime_error.h"

#define FRAMEBUFFER_ELEMENTS ((FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT)/(8UL * 8UL))

#define ASCII_OFFSET          (32U)
#define MAX_STRING_LENGTH    (100U)

static uint64_t framebuffer_array[FRAMEBUFFER_ELEMENTS];

/* cppcheck-suppress unusedStructMember */
STATIC_ASSERT(sizeof(framebuffer_array) == (128UL * sizeof(framebuffer_array[0])), framebuffer_should_contain_128_elements);

/*
 * @brief Initializes the framebuffer and clears it.
 */
fb_handle_t framebuffer_init(void)
{
    fb_handle_t framebuffer_ptr = (fb_handle_t) framebuffer_array;

    framebuffer_clear(framebuffer_ptr);

    return framebuffer_ptr;
}

/*
 * @brief Clears the whole framebuffer.
 */
void framebuffer_clear(fb_handle_t const framebuffer)
{
    for (uint8_t i = 0; i < FRAMEBUFFER_ELEMENTS; i++)
    {
        framebuffer[i] = 0;
    }
}

/*
 * @brief Changes (sets or resets) a single pixel of the framebuffer.
 */
void framebuffer_change_pixel(fb_handle_t const framebuffer, const uint8_t x, const uint8_t y, const bool set)
{
    if(x >= FRAMEBUFFER_WIDTH || y >= FRAMEBUFFER_HEIGHT)
    {
        RUNTIME_ERROR("Outside of framebuffer limits!");
        return; /* for unit tests */
    }

    if(set)
    {
        framebuffer[x + ((y & 0xF8) << 4)] |= 1 << (y & 7);
    }
    else
    {
        framebuffer[x + ((y & 0xF8) << 4)] &= ~(1 << (y & 7));
    }
}

/*
 * @brief Draws a single symbol (character) to the framebuffer.
 */
void framebuffer_draw_symbol(fb_handle_t const framebuffer, const uint8_t x, const uint8_t y, const uint8_t symbol)
{
    uint16_t ascii_symbol = (symbol - ASCII_OFFSET) * FONT_WIDTH;
    
    for (uint8_t dx = 0; dx < FONT_WIDTH; dx++)
    {
        for (uint32_t dy = 0; dy < FONT_HEIGHT; dy++)
        {
            framebuffer_change_pixel(framebuffer, dx + x, dy + y, image_get_pixel(dx, dy, &ssd1306xled_font6x8[ascii_symbol]));
        }
    }
}

/*
 * @brief Outputs a string to the framebuffer.
 */
void framebuffer_draw_string(fb_handle_t const framebuffer, const uint8_t x, const uint8_t y, const char* string)
{
    /* check for null pointer */
    if(!string)
    {
        RUNTIME_ERROR("Null pointer received!");
        return; /* for unit tests */
    }

    /* initialize temp variables to start position of string */
    uint8_t temp_x = x;
    uint8_t temp_y = y;

    /* print every character of string */
    for(uint8_t i = 0; i < MAX_STRING_LENGTH; i++)
    {
        /* check if we have reached end of string */
        if((*(string + i)) == 0)
        {
            break;
        }

        /* check if we have reached end of line */
        if(temp_x + FONT_WIDTH > FRAMEBUFFER_WIDTH)
        {
            temp_x = 0;
            temp_y += FONT_HEIGHT;
        }

        /* do not print whitespaces at beginning of line */
        if((temp_x == 0) && (*(string + i) == ' '))
        {
            continue;
        }

        framebuffer_draw_symbol(framebuffer, temp_x, temp_y, *(string + i));

        temp_x += 7;
    }
}
