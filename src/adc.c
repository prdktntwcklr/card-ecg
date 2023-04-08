#include "adc.h"
#include "my_assert.h"

#include <stdbool.h>

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

/* holds the data from the ADC */
static int32_t adc_data = 0;

/* flag to check if peripheral is initialized or not */
static bool adc_is_initialized = false;

/**
 * @brief Initializes the ADC.
 */
void adc_init(void)
{
    /* disable all ADC interrupts */
    ADCMSKI = 0;

    /* set ADC clock to 512kHz for normal ADC operation */
    ADCMDE  |= ADCCLKSEL_512KHZ;

    /* configure ADC peripheral */
    ADC0CON |= ADC0CON_ADC0EN | ADC0CON_AMP_CM_AVDD_DIV_2 | \
               ADC0CON_CHANNEL_DIFF_0_1 | ADC0CON_REF_INT | \
               ADC0CON_GAIN_1;

    /* enable primary ADC result ready interrupt */
    ADCMSKI |= ADC0RDY_INTEN;

    /* set adc rate to 50 Hz */
    adc_set_rate(50);

    /* enable analog ground switch */
    ADCCFG = ADCCFG_GNDSW_EN;

    adc_is_initialized = true;
}

#ifdef TEST
/**
 * @brief Deinitializes the ADC.
 *
 * @note  Used for unit testing.
 */
/* cppcheck-suppress unusedFunction */
static void adc_deinit(void)
{
    adc_is_initialized = false;
}
#endif

/**
 * @brief Starts the ADC in continous mode and enables ADC interrupts.
 */
void adc_start(void)
{
    MY_ASSERT(adc_is_initialized);

    /* store contents of register */
    uint8_t adcmde_reg = ADCMDE;

    /* clear ADC operation mode configuration bits */
    adcmde_reg &= ~(0x7);

    /* set ADC to continous conversion mode */
    adcmde_reg |= ADCMDE_CONTINUOUS;

    /* write back to register */
    ADCMDE = adcmde_reg;

    /* enable ADC interrupts */
    IRQEN |= ADC_BIT;
}

/**
 * @brief Stops the ADC.
 */
/* cppcheck-suppress unusedFunction */
void adc_stop(void)
{
    MY_ASSERT(adc_is_initialized);

    /* power down ADC*/
    ADCMDE = ~0x07;

    /* disable ADC interrupts */
    IRQEN &= ~ADC_BIT;
}

/**
 * @brief Gets a value read in by the ADC.
 */
int32_t adc_get(void)
{
    MY_ASSERT(adc_is_initialized);

    /* disable ADC interrupts before accessing data */
    IRQEN &= ~ADC_BIT;

    int32_t temp_data = adc_data;

    /* reenable ADC interrupts */
    IRQEN |= ADC_BIT;

    return temp_data;
}

/**
 * @brief Sets the ADC rate.
 *
 * @note  Currently only supports 50 and 60 Hz.
 */
void adc_set_rate(uint16_t adc_rate)
{
    if(adc_rate == 50U)
    {
        ADCFLT = 127;
    }
    else if(adc_rate == 60U)
    {
        ADCFLT = 126;
    }
    else
    {
        /* adc_rate not supported */
        MY_ERROR();
    }
}

/**
 * @brief Sets the gain of the ADC.
 *
 * @note  Only certain values are supported, see p46.
 */
void adc_set_gain(uint16_t adc_gain)
{
    /* #lizard forgives (exclude from code complexity check) */

    /* store contents of register */
    uint16_t adc0con_reg = ADC0CON;

    /* clear gain bits */
    adc0con_reg &= ~ADC0CON_GAIN;

    switch(adc_gain)
    {
        case 1:
        {
            adc0con_reg |= ADC0CON_GAIN_1;
            break;
        }
        case 2:
        {
            adc0con_reg |= ADC0CON_GAIN_2;
            break;
        }
        case 4:
        {
            adc0con_reg |= ADC0CON_GAIN_4;
            break;
        }
        case 8:
        {
            adc0con_reg |= ADC0CON_GAIN_8;
            break;
        }
        case 16:
        {
            adc0con_reg |= ADC0CON_GAIN_16;
            break;
        }
        case 32:
        {
            adc0con_reg |= ADC0CON_GAIN_32;
            break;
        }
        case 64:
        {
            adc0con_reg |= ADC0CON_GAIN_64;
            break;
        }
        case 128:
        {
            adc0con_reg |= ADC0CON_GAIN_128;
            break;
        }
        case 256:
        {
            adc0con_reg |= ADC0CON_GAIN_256;
            break;
        }
        case 512:
        {
            adc0con_reg |= ADC0CON_GAIN_512;
            break;
        }
        default:
        {
            /* adc_gain not supported */
            MY_ERROR();
        }
    }

    /* update register */
    ADC0CON = adc0con_reg;
}

/**
 * @brief Handles the ADC interrupt.
 */
extern void adc_handle_interrupt(void)
{
    /* check if primary adc result is ready */
    if((ADCSTA & ADC0RDY) == ADC0RDY)
    {
        adc_data = ADC0DAT;
    }
}
/*** end of file ***/
