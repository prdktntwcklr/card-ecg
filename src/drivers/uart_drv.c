#include "drivers/uart_drv.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

/* values for a baud rate of 9600, see p81 of datasheet */
#define BAUD_9600_DL (0x0021UL)
#define BAUD_9600_M  (1UL)
#define BAUD_9600_N  (21UL)

/**
 * @brief Initializes the UART module. Uses a fixed baud rate of 9600.
 *
 * @note  Pin1.1 = SOUT
 */
extern void uart_drv_init(void)
{
    /* set alternative function for P1.1 */
    GP1CON |= (1UL << 4);

    /* bit 7 of COMCON0 has to be set before accessing COMDIV0 and COMDIV1 */
    COMCON0 |= (1U << 7);

    /* set DL value */
    uint16_t dl = (uint16_t)BAUD_9600_DL;
    COMDIV0 = dl & (0xFFU);
    COMDIV1 = (dl >> 8U) & (0xFFU);

    /* clear bit 7 of COMCON0 after accessing COMDIV0 and COMDIV1 */
    COMCON0 &= ~(1U << 7);

    /* set M and N values */
    COMDIV2 |= (BAUD_9600_M << 11) | (BAUD_9600_N << 0);

    /* set word length as 8 bits */
    COMCON0 |= (1U << 1) | (1U << 0);

    /* enable uart-related interrupts */
    IRQEN |= UART_BIT;
}

/**
 * @brief Enables the UART transmit buffer empty interrupt.
 */
__inline__ extern void uart_drv_enable_interrupt(void)
{
    COMIEN0 |= COMIEN0_TX_BUF_EMPTY;
}

/**
 * @brief Enables the UART transmit buffer empty interrupt.
 */
__inline__ extern void uart_drv_disable_interrupt(void)
{
    COMIEN0 &= ~COMIEN0_TX_BUF_EMPTY;
}

/**
 * @brief Returns true if the UART transmit buffer empty interrupt is enabled.
 */
__inline__ extern bool uart_drv_is_interrupt_enabled(void)
{
    return ((COMIEN0 & COMIEN0_TX_BUF_EMPTY) == COMIEN0_TX_BUF_EMPTY);
}

/**
 * @brief Sends a byte of data over UART.
 */
__inline__ extern void uart_drv_send_byte(uint8_t byte)
{
    COMTX = byte;
}

__inline__ extern bool is_tx_buf_empty_interrupt(void)
{
    return ((COMIID0 & COMIID_TX_BUF_EMPTY) == COMIID_TX_BUF_EMPTY);
}
/*** end of file ***/
