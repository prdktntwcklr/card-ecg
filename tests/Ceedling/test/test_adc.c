#ifdef TEST

#include "unity.h"

#define EXTERN

#include "adc.c" /* hack to test static functions */
#include "adc.h"
#include "my_assert_stub.h"
#include "testable_mcu_registers.h"

void setUp(void)
{
    ADCMDE = 0x03;    /* default value */
    ADC0CON = 0x8000; /* default value */
    ADCMSKI = 0;
    ADCFLT = 0x0007;  /* default value */
    ADCCFG = 0;
    IRQEN = 0;
    ADC0DAT = 0;
}

void tearDown(void)
{
    adc_deinit();
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
    TEST_ASSERT_FAIL_ASSERT(adc_set_rate(0));
    TEST_ASSERT_FAIL_ASSERT(adc_set_rate(70));
    TEST_ASSERT_FAIL_ASSERT(adc_set_rate(256));
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
    TEST_ASSERT_FAIL_ASSERT(adc_set_gain(0));
    TEST_ASSERT_FAIL_ASSERT(adc_set_gain(3));
    TEST_ASSERT_FAIL_ASSERT(adc_set_gain(13));
}

void test_adc_start_should_startAdcPeripgeral(void)
{
    adc_init();
    adc_start();

    TEST_ASSERT_EQUAL_HEX8(0x81, ADCMDE);
    TEST_ASSERT_EQUAL_HEX32(0x00000400, IRQEN);
}

void test_adc_start_should_throwErrorIfAdcIsNotInitialized(void)
{
    TEST_ASSERT_FAIL_ASSERT(adc_start());
}

void test_adc_stop_should_throwErrorIfAdcIsNotInitialized(void)
{
    TEST_ASSERT_FAIL_ASSERT(adc_stop());
}

void test_adc_stop_should_turnOffAdcAndAdcInterrupt(void)
{
    adc_init();

    ADCMDE = 0xFF;
    IRQEN = 0xFFFFFFFF;

    adc_stop();

    TEST_ASSERT_EQUAL_HEX8(0xF8, ADCMDE);
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFBFF, IRQEN);
}

void test_adc_get_should_returnCorrectDataFromAdc(void)
{
    adc_init();

    ADC0DAT = 0;
    adc_handle_interrupt();
    TEST_ASSERT_EQUAL_INT32(0, adc_get());

    ADC0DAT = 0x1234;
    adc_handle_interrupt();
    TEST_ASSERT_EQUAL_INT32(0, adc_get());
}

#endif // TEST
