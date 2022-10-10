#include "framebuffer.h"
#include "font.h"
#include "image.h"
#include "runtime_error.h"

#define FRAMEBUFFER_ELEMENTS ((FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT)/(8UL * 8UL))

#define ASCII_OFFSET          (32U)
#define MAX_STRING_LENGTH    (100U)

static fb_handle_t framebuffer_ptr;
static uint64_t framebuffer_array[FRAMEBUFFER_ELEMENTS];

bool framebuffer_is_initialized = false;

/* cppcheck-suppress unusedStructMember */
STATIC_ASSERT(sizeof(framebuffer_array) == (128UL * sizeof(framebuffer_array[0])), framebuffer_should_contain_128_elements);

/*
 * @brief Initializes the framebuffer and clears it.
 */
void framebuffer_init(void)
{
    if(framebuffer_is_initialized == true)
    {
        RUNTIME_ERROR("Framebuffer is already initialized!");
    }

    framebuffer_ptr = (fb_handle_t) framebuffer_array;

    framebuffer_clear(framebuffer_ptr);

    framebuffer_is_initialized = true;
}

/*
 * @brief Denitializes the framebuffer.
 *
 * @note  Helper function for unit testing.
 */
/* cppcheck-suppress unusedFunction */
__attribute__((unused)) static void framebuffer_deinit(void)
{
    framebuffer_is_initialized = false;

    framebuffer_ptr = 0;
}

/*
 * @brief Clears the whole framebuffer.
 */
void framebuffer_clear(fb_handle_t const framebuffer)
{
    if(!framebuffer)
    {
        RUNTIME_ERROR("Null pointer received!");
        return; /* for unit tests */
    }

    for (uint8_t i = 0; i < FRAMEBUFFER_ELEMENTS; i++)
    {
        framebuffer[i] = 0;
    }
}

/*
 * @brief Returns the framebuffer.
 */
fb_handle_t framebuffer_get(void)
{
    if(framebuffer_is_initialized == false)
    {
        RUNTIME_ERROR("Framebuffer must be initialized first!");
        return 0;
    }

    return framebuffer_ptr;
}

/*
 * @brief Changes (sets or resets) a single pixel of the framebuffer.
 */
void framebuffer_change_pixel(fb_handle_t const framebuffer, const uint8_t x, const uint8_t y, const bool set)
{
    if(!framebuffer)
    {
        RUNTIME_ERROR("Null pointer received!");
        return; /* for unit tests */
    }

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
    if(!string)
    {
        RUNTIME_ERROR("Null pointer received!");
        return; /* for unit tests */
    }

    /* initialize variables to start position of string */
    uint8_t next_x_pos = x;
    uint8_t next_y_pos = y;

    /* print every character of string */
    for(uint8_t i = 0; i < MAX_STRING_LENGTH; i++)
    {
        char next_symbol = *(string + i);

        /* check if we have reached end of string */
        if(next_symbol == 0)
        {
            break;
        }

        /* check if we have reached end of line */
        if((next_x_pos + FONT_WIDTH) > FRAMEBUFFER_WIDTH)
        {
            /* switch to next line */
            next_x_pos = x;
            next_y_pos += FONT_HEIGHT;
        }

        /* skip whitespace at beginning of line */
        if((next_x_pos == 0) && (next_symbol == ' '))
        {
            continue;
        }

        framebuffer_draw_symbol(framebuffer, next_x_pos, next_y_pos, next_symbol);

        next_x_pos += (FONT_WIDTH + 1);
    }
}
