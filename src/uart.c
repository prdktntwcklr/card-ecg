#include "uart.h"

#include <stdbool.h>

#include "runtime_error.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

static bool uart_is_initialized = false;

/*
 * @brief Initializes the uart module.
 *
 * @note  Pin1.1 = SOUT
 */
void uart_init(const uint32_t baud_rate)
{
    /* check for baud_rate of zero */
    if(baud_rate == 0)
    {
        RUNTIME_ERROR("Uart baud rate cannot be zero!");
        return; /* for unit tests */
    }

    /* set alternative function for P1.1 */
    GP1CON |= (1UL << 4);

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
