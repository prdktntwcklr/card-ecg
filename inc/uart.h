#ifndef UART_H
#define UART_H

#include <stdbool.h>
#include <stdint.h>

void uart_init(void);
void uart_handle_interrupt(void);

#endif // UART_H
/*** end of file ***/
