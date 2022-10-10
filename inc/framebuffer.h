#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "stdbool.h"
#include "stdint.h"

#define FRAMEBUFFER_WIDTH    (128UL)
#define FRAMEBUFFER_HEIGHT    (64UL)

uint8_t* framebuffer_init(void);
void framebuffer_change_pixel(uint8_t * const framebuffer, const uint8_t x, const uint8_t y, const bool set);

#endif // FRAMEBUFFER_H
