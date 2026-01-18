#include "drivers/uart.h"

#include "drivers/system.h"
#include "drivers/uart_drv.h"
#include "utils/my_assert.h"
#include "utils/ring_buffer.h"

#ifndef NPRINTF /* NPRINTF not defined -- printf enabled */

/* flag to check if peripheral is initialized or not */
static bool uart_is_initialized = false;

/* max number of characters allowed to send */
#define MAX_UART_LENGTH (100U) /* characters */

/**
 * @brief Initializes the UART module. Uses a fixed baud rate of 9600.
 */
void uart_init(void)
{
    uart_drv_init();

    ring_buffer_reset();

    uart_drv_disable_interrupt();

    uart_is_initialized = true;
}

#ifdef TEST
/**
 * @brief Deinitializes the UART module.
 *
 * @note  Used for unit testing.
 */
/* cppcheck-suppress unusedFunction */
void uart_deinit(void)
{
    uart_is_initialized = false;
}
#endif

/**
 * @brief Handles the UART interrupt.
 */
extern void uart_handle_interrupt(void)
{
    /* check if we are receiving the correct interrupt */
    if(is_tx_buf_empty_interrupt())
    {
        /* send the next symbol over UART */
        uint8_t next_symbol = 0;

        bool more_to_send = ring_buffer_get(&next_symbol);

        if(more_to_send)
        {
            uart_drv_send_byte(next_symbol);
        }
        else /* could not get next symbol, ring buffer is empty */
        {
            /* stop sending by turning off interrupt */
            uart_drv_disable_interrupt();
        }
    }
}

/**
 * @brief Putchar implementation for using printf library.
 */
/* cppcheck-suppress * */
extern void putchar_(char c)
{
    MY_ASSERT(uart_is_initialized);

    (void)ring_buffer_put(c);

    if(!uart_drv_is_interrupt_enabled())
    {
        uint8_t first_symbol = 0;

        (void)ring_buffer_get(&first_symbol);

        uart_drv_send_byte(first_symbol);

        uart_drv_enable_interrupt();
    }
}

#else /* NPRINTF defined -- printf disabled */

/* stub out uart functions if printf is not used */
extern void uart_init(void) {}
extern void uart_handle_interrupt(void) {}

#endif /* NPRINTF */
/*** end of file ***/
