/* testable_mcu_registers.h */

#ifndef TESTABLE_MCU_REGISTERS_H
#define TESTABLE_MCU_REGISTERS_H

#include <stdint.h>

#ifndef EXTERN
#define EXTERN extern
#endif

// GPIO ports
EXTERN  uint32_t  GP0CON0;
EXTERN  uint16_t  GP0KEY1;
    #define  GP0KEY1_KEY  (0x07)
EXTERN  uint8_t   GP0CON1;
EXTERN  uint16_t  GP0KEY2;
    #define  GP0KEY2_KEY  (0x13)
EXTERN  uint32_t  GP0DAT;
EXTERN  uint32_t  GP0SET;
EXTERN  uint32_t  GP0CLR;
EXTERN  uint32_t  GP0PAR;

EXTERN  uint32_t  GP1CON;
EXTERN  uint32_t  GP1DAT;
EXTERN  uint32_t  GP1SET;
EXTERN  uint32_t  GP1CLR;
EXTERN  uint32_t  GP1PAR;

EXTERN  uint32_t  GP2CON;
EXTERN  uint32_t  GP2DAT;
EXTERN  uint32_t  GP2SET;
EXTERN  uint32_t  GP2CLR;
EXTERN  uint32_t  GP2PAR;


// Interrupt controller
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

EXTERN  uint32_t  IRQSTA;
EXTERN  uint32_t  IRQSIG;
EXTERN  uint32_t  IRQEN;
EXTERN  uint32_t  IRQCLR;
EXTERN  uint32_t  SWICFG;
EXTERN  uint32_t  IRQBASE;
EXTERN  uint32_t  IRQVEC;
EXTERN  uint32_t  IRQP0;
EXTERN  uint32_t  IRQP1;
EXTERN  uint32_t  IRQP2;
EXTERN  uint32_t  IRQCONN;
EXTERN  uint32_t  IRQCONE;
EXTERN  uint32_t  IRQCLRE;
EXTERN  uint32_t  IRQSTAN;
EXTERN  uint32_t  FIQSTA;
EXTERN  uint32_t  FIQSIG;
EXTERN  uint32_t  FIQEN;
EXTERN  uint32_t  FIQCLR;
EXTERN  uint32_t  FIQVEC;
EXTERN  uint32_t  FIQSTAN;

// System control
EXTERN  uint8_t   REMAP;
enum
{
    REMAP_FLASH               = (0UL << 0),
    REMAP_SRAM                = (1UL << 0)
};

EXTERN uint8_t RSTSTA;
enum
{
    RESET_SRC_POR             = (1UL << 0),
    RESET_SRC_WDT             = (1UL << 1),
    RESET_SRC_SOFT            = (1UL << 2),
    RESET_SRC_EXTERNAL        = (1UL << 3)
};

EXTERN  uint8_t   RSTCLR;

// Timer 0
EXTERN  uint32_t  T0LD;
EXTERN  uint32_t  T0VAL;
EXTERN  uint32_t  T0CON;
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

EXTERN  uint8_t   T0CLRI;
EXTERN  uint32_t  T0CAP;

// Timer 1 = Wake-up timer
EXTERN  uint32_t  T1LD;
EXTERN  uint32_t  T1VAL;
EXTERN  uint16_t  T1CON;
enum
{
    T1_DIV_1                  = (0UL << 0),
    T1_DIV_16                 = (4UL << 0),
    T1_DIV_256                = (8UL << 0),
    T1_DIV_32768              = (0xFUL <<    0),
    
    T1_BINARY                 = (0UL << 4),
    T1_24_HOURS               = (2UL << 4),
    T1_255_HOURS              = (3UL << 4),

    T1_FREE_RUNNING           = (0UL << 6),
    T1_PERIODIC               = (1UL << 6),

    T1_DISABLED               = (0UL << 7),
    T1_ENABLED                = (1UL << 7),

    T1_DOWN                   = (0UL << 8),
    T1_UP                     = (1UL << 8),

    T1_32KHZ                  = (0UL << 9),
    T1_10MHZ_CD               = (1UL << 9),
    T1_XTALI                  = (2UL << 9),
    T1_10MHZ                  = (3UL << 9)
};

EXTERN  uint8_t   T1CLRI;

// Timer 2 = Watchdog timer
EXTERN  uint16_t  T2LD;
EXTERN  uint16_t  T2VAL;
EXTERN  uint16_t  T2CON;
enum
{
    T2_RUN_IN_POWERDOWN       = (0UL << 0),
    T2_STOP_IN_POWERDOWN      = (1UL << 0),
    
    T2_WDT_ACTION_RESET       = (0UL << 1),
    T2_WDT_ACTION_IRQ         = (1UL << 1),

    T2_32KHZ_DIV_1            = (0UL << 2),
    T2_32KHZ_DIV_16           = (1UL << 2),
    T2_32KHZ_DIV_256          = (2UL << 2),

    T2_TIMER_MODE             = (0UL << 5),
    T2_WDT_MODE               = (1UL << 5),

    T2_FREE_RUNNING           = (0UL << 6),
    T2_PERIODIC               = (1UL << 6),

    T2_DISABLED               = (0UL << 7),
    T2_ENABLED                = (1UL << 7),

    T2_DOWN                   = (0UL << 8),
    T2_UP                     = (1UL << 8)
};
EXTERN  uint8_t   T2CLRI;

// Timer 3
EXTERN  uint16_t  T3LD;
EXTERN  uint16_t  T3VAL;
EXTERN  uint32_t  T3CON;
enum
{
    T3_DIV_1                  = (0UL << 0),
    T3_DIV_16                 = (4UL << 0),
    T3_DIV_256                = (8UL << 0),
    T3_DIV_32768              = (0xFUL << 0),
    
    T3_FREE_RUNNING           = (0UL << 6),
    T3_PERIODIC               = (1UL << 6),

    T3_DISABLED               = (0UL << 7),
    T3_ENABLED                = (1UL << 7),

    T3_DOWN                   = (0UL << 8),
    T3_UP                     = (1UL << 8),

    T3_32KHZ                  = (0UL << 9),
    T3_10MHZ_CD               = (1UL << 9),
    T3_10MHZ                  = (2UL << 9),

    T3_EVENT_T0               = (1UL << 12),
    T3_EVENT_T1               = (2UL << 12),
    T3_EVENT_T2               = (3UL << 12),
    T3_EVENT_T3               = (4UL << 12),
    T3_EVENT_ADC              = (8UL << 12),
    T3_EVENT_UART             = (9UL << 12),
    T3_EVENT_SPI              = (10UL << 12),
    T3_EVENT_EXT_IRQ0         = (11UL << 12),
    T3_EVENT_EXT_IRQ1         = (12UL << 12),
    T3_EVENT_I2C_MASTER       = (13UL << 12),
    T3_EVENT_I2C_SLAVE        = (14UL << 12),
    T3_EVENT_PWM              = (15UL << 12),
    T3_EVENT_EXT_IRQ2         = (16UL << 12),
    T3_EVENT_EXT_IRQ3         = (17UL << 12),

    T3_EVENT_DISABLED         = (0UL <<  17),
    T3_EVENT_ENABLED          = (1UL <<  17)
};
EXTERN  uint8_t   T3CLRI;
EXTERN  uint16_t  T3CAP;

// PLL
EXTERN  uint16_t  PLLKEY1;
    #define  PLLKEY1_KEY  (0xAA)
EXTERN  uint8_t   PLLCON;
enum
{
    PLL_CLK_INT_32KHZ         = (0UL << 0),
    PLL_CLK_EXT_32KHZ         = (2UL << 0),
    PLL_CLK_EXT_P20           = (1UL << 2)
};
EXTERN  uint16_t  PLLKEY2;
    #define  PLLKEY2_KEY  (0x55)

// Power control
EXTERN  uint16_t  POWKEY1;
    #define  POWKEY1_KEY  (1)
EXTERN  uint8_t   POWCON0;
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
EXTERN  uint16_t  POWKEY2;
    #define  POWKEY2_KEY  (0xF4)

EXTERN  uint16_t  POWKEY3;
    #define  POWKEY3_KEY  (0x76)
EXTERN  uint16_t  POWCON1;
enum
{
    I2C_SPI_POWER_ON          = (1UL << 2),
    UART_POWER_ON             = (1UL << 5),
    PWM_POWER_ON              = (1UL << 8)
};
EXTERN  uint16_t  POWKEY4;
    #define  POWKEY4_KEY  (0xB1)

// UART
EXTERN  uint8_t   COMTX;
EXTERN  uint8_t   COMRX;
EXTERN  uint8_t   COMDIV0;
EXTERN  uint8_t   COMIEN0;
enum
{
    COMIEN0_RX_BUF_FULL       = (1 << 0),
    COMIEN0_TX_BUF_EMPTY      = (1 << 1),
    COMIEN0_RX_STATUS         = (1 << 2),
    COMIEN0_MODEM_STATUS      = (1 << 3)
};
EXTERN  uint8_t   COMDIV1;
EXTERN  uint8_t   COMIID0;
enum
{
    COMIID_NO_INTERRUPT       = (1 << 0),
    COMIID_MODEM_STATUS       = (0 << 1),
    COMIID_TX_BUF_EMPTY       = (1 << 1),
    COMIID_RX_BUF_FULL        = (2 << 1),
    COMIID_RX_STATUS          = (3 << 1)
};
EXTERN  uint8_t   COMCON0;
enum
{
    COMCON0_DATABITS_5        = (0 << 0),
    COMCON0_DATABITS_6        = (1 << 0),
    COMCON0_DATABITS_7        = (2 << 0),
    COMCON0_DATABITS_8        = (3 << 0),

    COMCON0_STOPBITS_1        = (0 << 2),
    COMCON0_STOPBITS_1_5      = (1 << 2),

    COMCON0_PARITY_NONE       = (0 << 3),
    COMCON0_PARITY_ENABLE     = (1 << 3),

    COMCON0_PARITY_ODD        = (0 << 4),
    COMCON0_PARITY_EVEN       = (1 << 4),

    COMCON0_PARITY_STICK      = (1 << 5),

    COMCON0_BREAK_ENABLE      = (1 << 6),
    COMCON0_ACCESS_DL         = (1 << 7)
};
EXTERN  uint8_t   COMCON1;
EXTERN  uint8_t   COMSTA0;
enum
{
    DATA_READY                = (1 << 0),
    OVERRUN_ERR               = (1 << 1),
    PARITY_ERR                = (1 << 2),
    FRAMING_ERR               = (1 << 3),
    BREAK_RECEIVED            = (1 << 4),
    TX_BUF_EMPTY              = (1 << 5),
    TX_DONE                   = (1 << 6)
};
EXTERN  uint8_t   COMSTA1;
EXTERN  uint16_t  COMDIV2;

// ADC
EXTERN  uint16_t  ADCSTA;
enum
{
    ADC0RDY                   = (1 << 0),
    ADC1RDY                   = (1 << 1),
    ADC0OVR                   = (1 << 3),
    ADC0THEX                  = (1 << 4),
    ADC0ATHEX                 = (1 << 6),
    ADC0CERR                  = (1 << 12),
    ADC1CERR                  = (1 << 13),
    ADCCALSTA                 = (1 << 15)
};
EXTERN  uint16_t  ADCMSKI;
enum
{
    ADC0RDY_INTEN             = (1 << 0),
    ADC1RDY_INTEN             = (1 << 1),
    ADC0OVR_INTEN             = (1 << 3),
    ADC0THEX_INTEN            = (1 << 4),
    ADC0ATHEX_INTEN           = (1 << 6)
};
EXTERN  uint8_t  ADCMDE;
enum
{
    ADCMDE_ADCMD              = (7 << 0),
    ADCMDE_POWERDOWN          = (0 << 0),
    ADCMDE_CONTINUOUS         = (1 << 0),
    ADCMDE_SINGLE             = (2 << 0),
    ADCMDE_IDLE               = (3 << 0),
    ADCMDE_OFFSET_CAL         = (4 << 0),
    ADCMDE_GAIN_CAL           = (5 << 0),
    ADCMDE_ZERO_CAL           = (6 << 0),
    ADCMDE_FULL_CAL           = (7 << 0),

    ADCMDE_LPMCFG             = (3 << 3),
    ADCMDE_NORMAL_POWER       = (0 << 3),
    ADCMDE_LOW_POWER          = (1 << 3),
    ADCMDE_NORMAL_POWER2      = (2 << 3),
    ADCMDE_LOW_POWER_PLUS     = (3 << 3),

    ADCLPMEN                  = (1 << 4),

    ADCCLKSEL_131KHZ          = (0 << 7),
    ADCCLKSEL_512KHZ          = (1 << 7)

};
EXTERN  uint16_t  ADC0CON;
enum
{
    ADC0CON_GAIN              = (0xF << 0),
    ADC0CON_GAIN_1            = (0 << 0),
    ADC0CON_GAIN_2            = (1 << 0),
    ADC0CON_GAIN_4            = (2 << 0),
    ADC0CON_GAIN_8            = (3 << 0),
    ADC0CON_GAIN_16           = (4 << 0),
    ADC0CON_GAIN_32           = (5 << 0),
    ADC0CON_GAIN_64           = (6 << 0),
    ADC0CON_GAIN_128          = (7 << 0),
    ADC0CON_GAIN_256          = (8 << 0),
    ADC0CON_GAIN_512          = (9 << 0),

    ADC0CON_REF               = (3 << 4),
    ADC0CON_REF_INT           = (0 << 4),
    ADC0CON_REF_EXT           = (1 << 4),
    ADC0CON_REF_EXT_AUX       = (2 << 4),
    ADC0CON_REF_AVDD_DIV_2    = (3 << 4),

    ADC0CON_CHANNEL           = (0xF << 6),
    ADC0CON_CHANNEL_DIFF_0_1  = (0 << 6),
    ADC0CON_CHANNEL_0_5       = (1 << 6),
    ADC0CON_CHANNEL_1_5       = (2 << 6),
    ADC0CON_CHANNEL_VREF      = (3 << 6),
    ADC0CON_CHANNEL_DIFF_2_3  = (5 << 6),
    ADC0CON_CHANNEL_2_5       = (6 << 6),
    ADC0CON_CHANNEL_3_5       = (7 << 6),
    ADC0CON_CHANNEL_SHORT_0   = (8 << 6),
    ADC0CON_CHANNEL_SHORT_1   = (9 << 6),

    ADC0CON_CODE_2_COMPLEMENT = (0 << 10),
    ADC0CON_CODE_UNIPOLAR     = (1 << 10),

    ADC0CON_AMP_CM_ZERO       = (0 << 11),
    ADC0CON_AMP_CM_AVDD_DIV_2 = (1 << 11),

    ADC0CON_EXTREF_MORE_1_35V = (1 << 12),

    ADC0CON_DIAG              = (3 << 13),
    ADC0CON_DIAG_OFF          = (0 << 13),
    ADC0CON_DIAG_POSITIVE     = (1 << 13),
    ADC0CON_DIAG_NEGATIVE     = (2 << 13),
    ADC0CON_DIAG_BOTH         = (3 << 13),

    ADC0CON_ADC0EN            = (1 << 15)
};
EXTERN  uint16_t  ADC1CON;
enum
{
    ADC1CON_GAIN              = (3 << 0),
    ADC1CON_GAIN_1            = (0 << 0),
    ADC1CON_GAIN_2            = (1 << 0),
    ADC1CON_GAIN_4            = (2 << 0),
    ADC1CON_GAIN_8            = (3 << 0),

    ADC1CON_BUFF              = (3 << 2),
    ADC1CON_BUFF_ON           = (0 << 2),
    ADC1CON_BUFF_POSITIVE     = (1 << 2),
    ADC1CON_BUFF_NEGATIVE     = (2 << 2),
    ADC1CON_BUFF_OFF          = (3 << 2),

    ADC1CON_REF               = (7 << 4),
    ADC1CON_REF_INT           = (0 << 4),
    ADC1CON_REF_EXT           = (1 << 4),
    ADC1CON_REF_EXT_AUX       = (2 << 4),
    ADC1CON_REF_AVDD_DIV_2    = (3 << 4),
    ADC1CON_REF_AVDD_ADC3     = (4 << 4),

    ADC1CON_CHANNEL           = (0xF << 7),
    ADC1CON_CHANNEL_2_3_DIFF  = (0 << 7),
    ADC1CON_CHANNEL_4_5_DIFF  = (1 << 7),
    ADC1CON_CHANNEL_6_7_DIFF  = (2 << 7),
    ADC1CON_CHANNEL_8_9_DIFF  = (3 << 7),
    ADC1CON_CHANNEL_2_5       = (4 << 7),
    ADC1CON_CHANNEL_3_5       = (5 << 7),
    ADC1CON_CHANNEL_4_5       = (6 << 7),
    ADC1CON_CHANNEL_6_5       = (7 << 7),
    ADC1CON_CHANNEL_7_5       = (8 << 7),
    ADC1CON_CHANNEL_8_5       = (9 << 7),
    ADC1CON_CHANNEL_9_5       = (10 << 7),
    ADC1CON_CHANNEL_TEMP      = (11 << 7),
    ADC1CON_CHANNEL_VREF      = (12 << 7),
    ADC1CON_CHANNEL_DAC       = (13 << 7),
    ADC1CON_CHANNEL_ADC3      = (15 << 7),

    ADC1CON_CODE_2_COMPLEMENT = (0 << 11),
    ADC1CON_CODE_UNIPOLAR     = (1 << 11),

    ADC1CON_EXTREF_MORE_1_35V = (1 << 12),

    ADC1CON_DIAG              = (3 << 13),
    ADC1CON_DIAG_OFF          = (0 << 13),
    ADC1CON_DIAG_POSITIVE     = (1 << 13),
    ADC1CON_DIAG_NEGATIVE     = (2 << 13),
    ADC1CON_DIAG_BOTH         = (3 << 13),

    ADC1CON_ADC0EN            = (1 << 15)
};
EXTERN  uint16_t  ADCFLT;
enum
{
    ADCFLT_FREQ               = (0x7F << 0),
    ADCFLT_FREQ_1000HZ        = (7 << 0),
    ADCFLT_FREQ_500HZ         = (15 << 0),
    ADCFLT_FREQ_200HZ         = (39 << 0),
    ADCFLT_FREQ_100HZ         = (79 << 0),
    ADCFLT_FREQ_60HZ          = (126 << 0),
    ADCFLT_FREQ_50HZ          = (127 << 0),

    ADCFLT_NOTCH2             = (1 << 7),

    ADCFLT_AVG_FACTOR         = (0x3F << 8),

    ADCFLT_RUNNING_AVERAGE    = (1 << 14),
    ADCFLT_CHOP_ENABLE        = (1 << 15)
};
EXTERN  uint8_t  ADCCFG;
enum
{
    ADCCFG_ADCRCEN            = (1 << 0),
    ADCCFG_GNDSW_RES_EN       = (1 << 1),
    ADCCFG_ADC0_OREN          = (1 << 2),

    ADCCFG_ADC0CMPEN_0        = (1 << 3),
    ADCCFG_ADC0CMPEN_1        = (1 << 4),

    ADCCFG_ADC0ACCEN_0        = (1 << 5),
    ADCCFG_ADC0ACCEN_1        = (1 << 6),

    ADCCFG_GNDSW_EN           = (1 << 7)
};
EXTERN  uint32_t  ADC0DAT;
EXTERN  uint32_t  ADC1DAT;
EXTERN  uint16_t  ADC0OF;
EXTERN  uint16_t  ADC1OF;
EXTERN  uint16_t  ADC0GN;
EXTERN  uint16_t  ADC1GN;
EXTERN  uint16_t  ADC0RCR;
EXTERN  uint16_t  ADC0RCV;
EXTERN  uint16_t  ADC0TH;
EXTERN  uint16_t  ADC0THC;
EXTERN  uint16_t  ADC0THV;
EXTERN  uint32_t  ADC0ACC;
EXTERN  uint32_t  ADC0ATH;
EXTERN  uint8_t   IEXCON;

// DAC
EXTERN  uint16_t  DAC0CON;
enum
{
    DAC0_RANGE_INTREF         = (0 << 0),
    DAC0_RANGE_EXTREF         = (1 << 0),
    DAC0_RANGE_EXTREF_ALT     = (2 << 0),
    DAC0_RANGE_AVDD           = (3 << 0),

    DAC0_RATE_UCLK_DIV_32     = (0 << 2),
    DAC0_RATE_UCLK_DIV_16     = (1 << 2),

    DAC0_MODE_12_BIT          = (0 << 3),
    DAC0_MODE_16_BIT          = (1 << 3),

    DAC0_CLEAR                = (0 << 4),
    DAC0_NORMAL_OPERATION     = (1 << 4),

    DAC0_CLOCK_HCLK           = (0 << 5),
    DAC0_CLOCK_TIMER1         = (1 << 5),

    DAC0_BUFFERED             = (0 << 6),
    DAC0_UNBUFFERED           = (1 << 6),

    DAC0_OPAMP_MODE           = (1 << 7),

    DAC0_BUF_LOW_POWER        = (1 << 8),

    DAC0_POWERDOWN            = (1 << 9)
};
EXTERN  uint32_t  DAC0DAT;

// Flash/EE memory
EXTERN  uint16_t  FEESTA;
enum
{
    FEESTA_COMMAND_DONE       = (1 << 0),
    FEESTA_COMMAND_FAIL       = (1 << 1),
    FEESTA_BUSY               = (1 << 2),
    FEESTA_IF                 = (1 << 3)
};
EXTERN  uint16_t  FEEMOD;
EXTERN  uint8_t   FEECON;
EXTERN  uint16_t  FEEDAT;
EXTERN  uint32_t  FEEADR;
EXTERN  uint32_t  FEESIGN;
EXTERN  uint32_t  FEEPRO;
EXTERN  uint32_t  FEEHIDE;

// I2C
EXTERN  uint32_t  I2CMCON;
EXTERN  uint32_t  I2CMSTA;
EXTERN  uint32_t  I2CMRX;
EXTERN  uint32_t  I2CMTX;
EXTERN  uint32_t  I2CMCNT0;
EXTERN  uint32_t  I2CMCNT1;
EXTERN  uint32_t  I2CADR0;
EXTERN  uint32_t  I2CADR1;
EXTERN  uint32_t  I2CREP;
EXTERN  uint32_t  I2CDIV;
EXTERN  uint32_t  I2CSCON;
EXTERN  uint32_t  I2CSSTA;
EXTERN  uint32_t  I2CSRX;
EXTERN  uint32_t  I2CSTX;
EXTERN  uint32_t  I2CALT;
EXTERN  uint32_t  I2CID0;
EXTERN  uint32_t  I2CID1;
EXTERN  uint32_t  I2CID2;
EXTERN  uint32_t  I2CID3;
EXTERN  uint32_t  I2CFSTA;
EXTERN  uint32_t  I2CRCON;

// SPI
EXTERN  uint32_t  SPISTA;
EXTERN  uint8_t   SPIRX;
EXTERN  uint8_t   SPITX;
EXTERN  uint8_t   SPIDIV;
EXTERN  uint16_t  SPICON;

// PWM
EXTERN  uint32_t  PWMBASE;
EXTERN  uint32_t  PWMCON;
EXTERN  uint32_t  PWM0COM0;
EXTERN  uint32_t  PWM0COM1;
EXTERN  uint32_t  PWM0COM2;
EXTERN  uint32_t  PWM0LEN;
EXTERN  uint32_t  PWM1COM0;
EXTERN  uint32_t  PWM1COM1;
EXTERN  uint32_t  PWM1COM2;
EXTERN  uint32_t  PWM1LEN;
EXTERN  uint32_t  PWM2COM0;
EXTERN  uint32_t  PWM2COM1;
EXTERN  uint32_t  PWM2COM2;
EXTERN  uint32_t  PWM2LEN;
EXTERN  uint32_t  PWMCLRI;

#endif // TESTABLE_MCU_REGISTERS_H
