#include "uart.h"

#include <stdbool.h>

#include "runtime_error.h"
#include "system.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

static bool uart_is_initialized = false;

/* Values for a baud rate of 9600, see p81 of datasheet */
#define BAUD_9600_DL (0x0021U)
#define BAUD_9600_M       (1U)
#define BAUD_9600_N      (21U)

#define MAX_UART_LENGTH (100U)

/*
 * @brief Initializes the uart module. Uses a fixed baud rate of 9600.
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

    uart_is_initialized = true;
}

#ifdef TEST
/*
 * @brief Deinitializes the uart module.
 *
 * @note  Used for unit testing.
 */
static void uart_deinit(void)
{
    uart_is_initialized = false;
}
#endif

/*
 * @brief Blocks until transmit buffer is empty.
 */
void uart_wait_for_buffer_empty(void)
{
    while((COMSTA0 & TX_BUF_EMPTY) == 0) {}
}

/*
 * @brief Sends a string through UART.
 */
void uart_send_string(const char *string)
{
    if(uart_is_initialized == false)
    {
        RUNTIME_ERROR("Uart is not initialized!");
        return; /* for unit tests */        
    }

    for(uint8_t i = 0; i < MAX_UART_LENGTH; i++)
    {
        char next_symbol = string[i];

        /* check for end of string */
        if(next_symbol == 0)
        {
            break;
        }

        uart_wait_for_buffer_empty();
        COMTX = next_symbol;
    }
}
