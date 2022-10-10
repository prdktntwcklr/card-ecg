#ifndef IMAGE_H
#define IMAGE_H

#include <stdbool.h>
#include <stdint.h>

bool image_get_pixel(const uint8_t x, const uint8_t y, const uint8_t* image);

#endif // IMAGE_H
