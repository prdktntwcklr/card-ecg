#ifdef TEST

#include "unity.h"

#define EXTERN 

#include "testable_mcu_registers.h"
#include "adc.h"
#include "adc.c" /* hack to test static functions */
#include "runtime_error_stub.h"

void setUp(void)
{
    ADCMDE = 0x03;    /* default value */
    ADC0CON = 0x8000; /* default value */
    ADCMSKI = 0;
    ADCFLT = 0x0007;  /* default value */
    ADCCFG = 0;

    runtime_error_stub_reset();
}

void tearDown(void)
{
}

void test_adc_init_should_initializeAdcCorrectly(void)
{
    adc_init();

    TEST_ASSERT_EQUAL_HEX8(0x83, ADCMDE);
    TEST_ASSERT_EQUAL_HEX16(0x8800, ADC0CON);
    TEST_ASSERT_EQUAL_HEX16(0x0001, ADCMSKI);
    TEST_ASSERT_EQUAL_INT(127, ADCFLT);
    TEST_ASSERT_EQUAL_HEX8(0x80, ADCCFG);
}

void test_adc_set_rate_should_setSupportedRatesCorrectly(void)
{
    adc_set_rate(50);
    TEST_ASSERT_EQUAL_INT(127, ADCFLT);

    adc_set_rate(60);
    TEST_ASSERT_EQUAL_INT(126, ADCFLT);

    /* unsupported rate */
    adc_set_rate(256);
    TEST_ASSERT_EQUAL_STRING("Adc rate not supported!", runtime_error_stub_get_last_error());
    TEST_ASSERT_EQUAL_INT(126, ADCFLT);
}

#endif // TEST
