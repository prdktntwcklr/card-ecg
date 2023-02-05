#include "uart.h"

#include "my_assert.h"
#include "ring_buffer.h"
#include "system.h"
#include "uart_drv.h"

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
static void uart_deinit(void)
{
    uart_is_initialized = false;
}
#endif

/**
 * @brief Sends a string through UART.
 */
void uart_send_string(const char *string)
{
    MY_ASSERT(uart_is_initialized);

    for(uint8_t i = 0; i < MAX_UART_LENGTH; i++)
    {
        uint8_t next_symbol = (uint8_t)string[i];

        /* check for end of string */
        if(next_symbol == 0)
        {
            break;
        }

        ring_buffer_put(next_symbol);
    }

    if(!uart_drv_is_interrupt_enabled())
    {
        uint8_t first_symbol = 0;

        ring_buffer_get(&first_symbol);

        uart_drv_send_byte(first_symbol);

        uart_drv_enable_interrupt();
    }
}

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
