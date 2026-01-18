#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdbool.h>
#include <stdint.h>

void ring_buffer_reset(void);
bool ring_buffer_put(uint8_t byte);
bool ring_buffer_get(uint8_t *byte);
bool ring_buffer_is_empty(void);
bool ring_buffer_is_full(void);

#endif // RING_BUFFER_H
/*** end of file ***/
