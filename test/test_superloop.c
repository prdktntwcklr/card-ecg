#ifdef TEST

#include "unity.h"

#define EXTERN 

#include "testable_mcu_registers.h"
#include "superloop.h"
#include "mock_led.h"
#include "mock_timer.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_superloop_init_should_initializePeripherals(void)
{
    system_init_Expect();
    led_init_Expect();
    timer_init_Expect();

    superloop_init();
}

void test_superloop_run_should_toggleLedIfDeadlineReached(void)
{
    timer_deadline_reached_IgnoreAndReturn(false);
    
    superloop_run();

    timer_deadline_reached_IgnoreAndReturn(true);
    led_toggle_Expect();

    superloop_run();
}

#endif // TEST
