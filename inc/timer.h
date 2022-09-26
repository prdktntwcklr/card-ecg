#ifndef TIMER_H
#define TIMER_H

#include "stdbool.h"
#include "stdint.h"

void system_init(void);
void timer_init(void);
bool timer_deadline_reached(const uint32_t deadline);
void timer_handle_interrupt(void);

#endif // TIMER_H
