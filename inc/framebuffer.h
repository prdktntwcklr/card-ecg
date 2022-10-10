#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "stdbool.h"
#include "stdint.h"

typedef uint8_t* fb_handle_t;

#define FRAMEBUFFER_WIDTH    (128UL)
#define FRAMEBUFFER_HEIGHT    (64UL)

fb_handle_t framebuffer_init(void);
void framebuffer_clear(fb_handle_t const framebuffer);
void framebuffer_change_pixel(fb_handle_t const framebuffer, const uint8_t x, const uint8_t y, const bool set);
void framebuffer_draw_symbol(fb_handle_t const framebuffer, const uint8_t x, const uint8_t y, const uint8_t symbol);
void framebuffer_draw_string(fb_handle_t const framebuffer, const uint8_t x, const uint8_t y, const char* string);

#endif // FRAMEBUFFER_H
