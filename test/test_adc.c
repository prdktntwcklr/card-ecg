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
}

void test_adc_set_rate_should_throwErrorIfRateNotSupported(void)
{
    adc_set_rate(60);
    TEST_ASSERT_EQUAL_INT(126, ADCFLT);

    adc_set_rate(256);
    TEST_ASSERT_EQUAL_STRING("Adc rate not supported!", runtime_error_stub_get_last_error());

    /* register should be untouched */
    TEST_ASSERT_EQUAL_INT(126, ADCFLT);
}

void test_adc_set_gain_should_setSupportedGainsCorrectly(void)
{
    adc_set_gain(1);
    TEST_ASSERT_EQUAL_HEX16(0x8000, ADC0CON);

    adc_set_gain(2);
    TEST_ASSERT_EQUAL_HEX16(0x8001, ADC0CON);

    adc_set_gain(4);
    TEST_ASSERT_EQUAL_HEX16(0x8002, ADC0CON);

    adc_set_gain(8);
    TEST_ASSERT_EQUAL_HEX16(0x8003, ADC0CON);

    adc_set_gain(16);
    TEST_ASSERT_EQUAL_HEX16(0x8004, ADC0CON);

    adc_set_gain(32);
    TEST_ASSERT_EQUAL_HEX16(0x8005, ADC0CON);

    adc_set_gain(64);
    TEST_ASSERT_EQUAL_HEX16(0x8006, ADC0CON);

    adc_set_gain(128);
    TEST_ASSERT_EQUAL_HEX16(0x8007, ADC0CON);

    adc_set_gain(256);
    TEST_ASSERT_EQUAL_HEX16(0x8008, ADC0CON);

    adc_set_gain(512);
    TEST_ASSERT_EQUAL_HEX16(0x8009, ADC0CON);    
}

void test_adc_set_gain_should_throwErrorIfGainNotSupported(void)
{
    adc_set_gain(128);
    TEST_ASSERT_EQUAL_HEX16(0x8007, ADC0CON);

    adc_set_gain(333);
    TEST_ASSERT_EQUAL_STRING("Adc gain not supported!", runtime_error_stub_get_last_error());

    /* register should be untouched */
    TEST_ASSERT_EQUAL_HEX16(0x8007, ADC0CON);
}

#endif // TEST
