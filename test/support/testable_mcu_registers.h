/* testable_mcu_registers.h */

#ifndef TESTABLE_MCU_REGISTERS_H
#define TESTABLE_MCU_REGISTERS_H

#include <stdint.h>

#ifndef EXTERN
#define EXTERN extern
#endif

EXTERN uint32_t GP1DAT;
EXTERN uint8_t  POWCON0;
enum
{
    CLK_10240_KHZ             = (0UL << 0),
    CLK_51200_KHZ             = (1UL << 0),
    CLK_2560_KHZ              = (2UL << 0),
    CLK_1280_KHZ              = (3UL << 0),
    CLK_640_KHZ               = (4UL << 0),
    CLK_320_KHZ               = (5UL << 0),
    CLK_160_KHZ               = (6UL << 0),
    CLK_80_KHZ                = (7UL << 0),

    CORE_POWER_ON             = (1UL << 3),
    PERIPH_POWER_ON           = (1UL << 4),
    PLL_POWER_ON              = (1UL << 5),
    XTAL_POWER_ON             = (1UL << 6)
};
EXTERN uint16_t POWKEY1;
#define POWKEY1_KEY (1)
EXTERN uint16_t POWKEY2;
#define POWKEY2_KEY (0xF4)
EXTERN uint32_t T0LD;
EXTERN uint32_t T0CON;
enum
{
    T0_DIV_1                  = (0UL << 0),
    T0_DIV_16                 = (4UL << 0),
    T0_DIV_256                = (8UL << 0),
    T0_DIV_32768              = (0xFUL << 0),
    
    T0_BINARY                 = (0UL << 4),
    T0_24_HOURS               = (2UL << 4),
    T0_255_HOURS              = (3UL << 4),

    T0_FREE_RUNNING           = (0UL << 6),
    T0_PERIODIC               = (1UL << 6),

    T0_DISABLED               = (0UL << 7),
    T0_ENABLED                = (1UL << 7),

    T0_DOWN                   = (0UL << 8),
    T0_UP                     = (1UL << 8),

    T0_32KHZ                  = (0UL << 9),
    T0_10MHZ_CD               = (1UL << 9),
    T0_10MHZ                  = (2UL << 9),
    T0_P1_0_CLK               = (3UL << 9),

    T0_EVENT_T0               = (1UL << 12),
    T0_EVENT_T1               = (2UL << 12),
    T0_EVENT_T2               = (3UL << 12),
    T0_EVENT_T3               = (4UL << 12),
    T0_EVENT_ADC              = (8UL << 12),
    T0_EVENT_UART             = (9UL << 12),
    T0_EVENT_SPI              = (10UL << 12),
    T0_EVENT_EXT_IRQ0         = (11UL << 12),
    T0_EVENT_EXT_IRQ1         = (12UL << 12),
    T0_EVENT_I2C_MASTER       = (13UL << 12),
    T0_EVENT_I2C_SLAVE        = (14UL << 12),
    T0_EVENT_PWM              = (15UL << 12),
    T0_EVENT_EXT_IRQ2         = (16UL << 12),
    T0_EVENT_EXT_IRQ3         = (17UL << 12),

    T0_EVENT_DISABLED         = (0UL << 17),
    T0_EVENT_ENABLED          = (1UL << 17),

    T0_INT_SRC_TIMER0         = (0UL << 18),
    T0_INT_SRC_POSTSCALER     = (1UL << 18),

    T0_POSTSCALER_FLAG        = (1UL << 19),

    T0_POSTSCALER_DISABLED    = (0UL << 23),
    T0_POSTSCALER_ENABLED     = (1UL << 23)
};
EXTERN uint32_t IRQEN;
enum 
{
    ALL_INT_FIQ               = (1UL << 0),
    SWI_BIT                   = (1UL << 1),

    TIMER0_BIT                = (1UL << 3),
    TIMER1_BIT                = (1UL << 4),
    TIMER2_BIT                = (1UL << 5),
    TIMER3_BIT                = (1UL << 6),

    ADC_BIT                   = (1UL << 10),
    UART_BIT                  = (1UL << 11),
    SPI_BIT                   = (1UL << 12),
    EXT_IRQ0_BIT              = (1UL << 13),
    EXT_IRQ1_BIT              = (1UL << 14),
    I2C_MASTER_BIT            = (1UL << 15),
    I2C_SLAVE_BIT             = (1UL << 16),
    PWM_BIT                   = (1UL << 17),
    EXT_IRQ2_BIT              = (1UL << 18),
    EXT_IRQ3_BIT              = (1UL << 19)
};
EXTERN uint32_t IRQSTA;
EXTERN uint8_t  T0CLRI;

#endif // TESTABLE_MCU_REGISTERS_H
