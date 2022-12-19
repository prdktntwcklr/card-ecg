#include "dac.h"

#include <stdbool.h>

#include "runtime_error.h"

#ifndef TEST
#include "aduc706x.h"
#else
#include "testable_mcu_registers.h"
#endif

/* maximum value allowed by the DAC */
#define DAC_MAX_VALUE (0xFFFU) /* 12 bit value */

/* flag to check if peripheral is initialized or not */
static bool dac_is_initialized = false;

/**
 * @brief Initializes the DAC.
 */
extern void dac_init(void)
{
    DAC0CON |= DAC0_NORMAL_OPERATION;

    dac_is_initialized = true;
}

#ifdef TEST
/**
 * @brief Deinitializes the DAC.
 *
 * @note  Used for unit testing.
 */
static void dac_deinit(void)
{
    DAC0CON &= ~DAC0_NORMAL_OPERATION;

    dac_is_initialized = false;
}
#endif

/**
 * @brief Sets the DAC output to some value.
 */
void dac_set(const uint16_t dac_value)
{
    if(dac_is_initialized == false)
    {
        RUNTIME_ERROR("Dac is not initialized!");
        return; /* for unit tests */
    }

    if(dac_value > DAC_MAX_VALUE)
    {
        RUNTIME_ERROR("Dac value > 0x0FFF!");
        return; /* for unit tests */        
    }

    DAC0DAT = ((uint32_t)dac_value << 16);
}
