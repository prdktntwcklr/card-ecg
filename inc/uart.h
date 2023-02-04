#ifndef UART_H
#define UART_H

#include <stdbool.h>
#include <stdint.h>

void uart_init(void);
void uart_send_string(const char *string);
bool uart_is_interrupt_enabled(void);
void uart_handle_interrupt(void);

#endif // UART_H
