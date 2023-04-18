#include "dac.h"

#include <stdbool.h>

#include "my_assert.h"

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
/* cppcheck-suppress unusedFunction */
static void dac_deinit(void)
{
    DAC0CON &= ~DAC0_NORMAL_OPERATION;

    dac_is_initialized = false;
}
#endif

/**
 * @brief Sets the DAC output to some value.
 */
void dac_set(uint16_t dac_value)
{
    MY_ASSERT(dac_is_initialized);
    MY_ASSERT(dac_value <= DAC_MAX_VALUE);

    DAC0DAT = ((uint32_t)dac_value << 16);
}
/*** end of file ***/
