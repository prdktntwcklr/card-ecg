#include "adc.h"

#include <stdbool.h>

#include "runtime_error.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

/* flag to check if peripheral is initialized or not */
static bool adc_is_initialized = false;

/*
 * @brief Initializes the ADC.
 */
void adc_init(void)
{
    /* disable all ADC interrupts */
    ADCMSKI = 0;

    /* set ADC clock to 512kHz for normal ADC operation */
    ADCMDE |= ADCCLKSEL_512KHZ;

    ADC0CON |= ADC0CON_ADC0EN | ADC0CON_AMP_CM_AVDD_DIV_2  | \
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
/*
 * @brief Deinitializes the ADC.
 *
 * @note  Used for unit testing.
 */
static void adc_deinit(void)
{
    adc_is_initialized = false;
}
#endif

/*
 * @brief Sets the ADC rate.
 *
 * @note  Currently only supports 50 and 60 Hz.
 */
void adc_set_rate(const uint16_t adc_rate)
{
    if(adc_rate == 50)
    {
        ADCFLT = 127;
    }
    else if(adc_rate == 60)
    {
        ADCFLT = 126;
    }
    else
    {
        RUNTIME_ERROR("Adc rate not supported!");
        return;
    }
}

/*
 * @brief Sets the gain of the ADC.
 */
void adc_set_gain(const uint16_t adc_gain)
{
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
            /* gain not supported, return without changing register */
            RUNTIME_ERROR("Adc gain not supported!");
            return;
        }
    }

    ADC0CON = adc0con_reg;
}
