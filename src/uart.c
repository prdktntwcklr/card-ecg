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

#define DL_VAL (0x0021U)
#define M_VAL       (1U)
#define N_VAL      (21U)

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

    /* DL for baud rate of 9600 is 0x21, see p81 of datasheet */
    uint16_t dl = DL_VAL;
    COMDIV0 = dl & (0xFF);
    COMDIV1 = (dl >> 8) & (0xFF);

    /* clear bit 7 of COMCON0 after accessing COMDIV0 and COMDIV1 */
    COMCON0 &= ~(1 << 7);

    /* M is 1, N is 21 */
    COMDIV2 |= (M_VAL << 11) | (N_VAL << 0);

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
void uart_deinit(void)
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
 * @brief Sends data through UART.
 */
void uart_send_data(const char *data)
{
    if(uart_is_initialized == false)
    {
        RUNTIME_ERROR("Uart is not initialized!");
        return; /* for unit tests */        
    }

    for(uint8_t i = 0; i < MAX_UART_LENGTH; i++)
    {
        if(data[i] == 0)
        {
            break;
        }

        uart_wait_for_buffer_empty();
        COMTX = data[i];
    }
}
