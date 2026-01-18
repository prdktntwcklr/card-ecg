#include "image.h"

/**
 * @brief Returns true if the pixel at x and y coordinates is set.
 */
bool image_get_pixel(const uint8_t *image, uint8_t x, uint8_t y)
{
    uint8_t byte = image[x + ((y & 0xF8U) << 4)];

    return ((byte & (1U << (y & 7U))));
}
/*** end of file ***/
