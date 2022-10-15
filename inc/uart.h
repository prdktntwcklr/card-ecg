#ifndef UART_H
#define UART_H

#include <stdint.h>

void uart_init(void);
void uart_send_data(const char *data);

#endif // UART_H
