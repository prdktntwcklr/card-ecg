#include "image.h"

bool image_get_pixel(const uint8_t x, const uint8_t y, const uint8_t* image)
{
    uint8_t byte = image[x + ((y & 0xF8) << 4)];
        
	return ((byte & (1 << (y & 7))));
}
