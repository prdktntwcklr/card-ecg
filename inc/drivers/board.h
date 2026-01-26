#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>

void set_led_pin_as_output(void);
void set_pin_as_output(uint8_t port, uint8_t pin);
void turn_led_pin_off(void);
void turn_led_pin_on(void);
void toggle_led_pin(void);

#endif // BOARD_H
