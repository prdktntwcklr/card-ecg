#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "stdbool.h"
#include "stdint.h"

typedef uint8_t* fb_handle_t;

#define FRAMEBUFFER_WIDTH    (128UL)
#define FRAMEBUFFER_HEIGHT    (64UL)

fb_handle_t framebuffer_init(void);
void framebuffer_change_pixel(fb_handle_t const framebuffer, const uint8_t x, const uint8_t y, const bool set);

#endif // FRAMEBUFFER_H
