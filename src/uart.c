#include "uart.h"

#include <stdbool.h>

#include "my_assert.h"
#include "ring_buffer.h"
#include "system.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

/* flag to check if peripheral is initialized or not */
static bool uart_is_initialized = false;

/* static function prototypes */
static bool uart_is_interrupt_enabled(void);
static void uart_wait_for_buffer_empty(void);
static void uart_enable_interrupt(void);
static void uart_disable_interrupt(void);

/* values for a baud rate of 9600, see p81 of datasheet */
#define BAUD_9600_DL (0x0021U)
#define BAUD_9600_M       (1U)
#define BAUD_9600_N      (21U)

/* max number of characters allowed to send */
#define MAX_UART_LENGTH (100U) /* characters */

/**
 * @brief Enables the UART transmit buffer empty interrupt.
 */
static void uart_enable_interrupt(void)
{
    COMIEN0 |= COMIEN0_TX_BUF_EMPTY;
}

/**
 * @brief Enables the UART transmit buffer empty interrupt.
 */
static void uart_disable_interrupt(void)
{
    COMIEN0 &= ~COMIEN0_TX_BUF_EMPTY;
}

/**
 * @brief Returns true if the UART transmit buffer empty interrupt is enabled.
 */
static bool uart_is_interrupt_enabled(void)
{
    return ((COMIEN0 & COMIEN0_TX_BUF_EMPTY) == COMIEN0_TX_BUF_EMPTY);
}

/**
 * @brief Initializes the UART module. Uses a fixed baud rate of 9600.
 *
 * @note  Pin1.1 = SOUT
 */
void uart_init(void)
{
    /* set alternative function for P1.1 */
    GP1CON |= (1UL << 4);

    /* bit 7 of COMCON0 has to be set before accessing COMDIV0 and COMDIV1 */
    COMCON0 |= (1 << 7);

    /* set DL value */
    uint16_t dl = BAUD_9600_DL;
    COMDIV0 = dl & (0xFF);
    COMDIV1 = (dl >> 8) & (0xFF);

    /* clear bit 7 of COMCON0 after accessing COMDIV0 and COMDIV1 */
    COMCON0 &= ~(1 << 7);

    /* set M and N values */
    COMDIV2 |= (BAUD_9600_M << 11) | (BAUD_9600_N << 0);

    /* set word length as 8 bits */
    COMCON0 |= (1 << 1) | (1 << 0);

    ring_buffer_reset();

    uart_is_initialized = true;
}

#ifdef TEST
/**
 * @brief Deinitializes the UART module.
 *
 * @note  Used for unit testing.
 */
static void uart_deinit(void)
{
    uart_is_initialized = false;
}
#endif

/**
 * @brief Blocks until transmit buffer is empty.
 */
static void uart_wait_for_buffer_empty(void)
{
    while((COMSTA0 & TX_BUF_EMPTY) == 0) {}
}

/**
 * @brief Sends a string through UART.
 * 
 * @todo  Should be interrupt-based by getting characters from ring buffer.
 */
void uart_send_string(const char *string)
{
    MY_ASSERT(uart_is_initialized);

    for(uint8_t i = 0; i < MAX_UART_LENGTH; i++)
    {
        char next_symbol = string[i];

        /* check for end of string */
        if(next_symbol == 0)
        {
            break;
        }

        ring_buffer_put(next_symbol);
    }

    if(!uart_is_interrupt_enabled())
    {
        char first_symbol;

        ring_buffer_get(&first_symbol);

        COMTX = first_symbol;

        uart_enable_interrupt();
    }
}
