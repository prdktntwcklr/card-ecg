#include "framebuffer.h"
#include "runtime_error.h"

#define FRAMEBUFFER_ELEMENTS ((FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT)/(8UL * 8UL))

#define ASCII_OFFSET           (32U)

uint64_t framebuffer_array[FRAMEBUFFER_ELEMENTS];

/* cppcheck-suppress unusedStructMember */
STATIC_ASSERT(sizeof(framebuffer_array) == (128UL * sizeof(framebuffer_array[0])), framebuffer_should_contain_128_elements);

/* static function declarations */
static void framebuffer_clear(fb_handle_t const framebuffer);

/*
 * @brief Clears the whole framebuffer.
 */
static void framebuffer_clear(fb_handle_t const framebuffer)
{
	for (uint8_t i = 0; i < FRAMEBUFFER_ELEMENTS; i++)
	{
		framebuffer[i] = 0;
	}
}

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
