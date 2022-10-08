#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

void display_init(void);
void display_send_framebuffer(const uint8_t *data);

#endif // DISPLAY_H
