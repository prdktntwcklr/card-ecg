#ifndef UART_DRV_H
#define UART_DRV_H

#include <stdbool.h>
#include <stdint.h>

void uart_drv_init(void);
void uart_drv_enable_interrupt(void);
void uart_drv_disable_interrupt(void);
bool uart_drv_is_interrupt_enabled(void);
void uart_drv_send_byte(uint8_t byte);
bool is_tx_buf_empty_interrupt(void);

#endif // UART_DRV_H
/*** end of file ***/
