#ifdef TEST

#include "unity.h"

#define EXTERN 

#include "testable_mcu_registers.h"

#include "logo.h"
#include "mock_display.h"
#include "mock_framebuffer.h"
#include "mock_led.h"
#include "mock_system.h"
#include "mock_timer.h"
#include "mock_uart.h"
#include "my_assert_stub.h"
#include "superloop.h"

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
    display_init_Expect();
    framebuffer_init_Expect();
    uart_init_Expect();
    uart_send_string_Expect("Hallo Welt!\r\n");

    superloop_init();
}

void test_superloop_run_should_notToggleLedIfDeadlineNotReached(void)
{
    timer_deadline_reached_IgnoreAndReturn(false);
    
    superloop_run();
}

void test_superloop_run_should_toggleLedIfDeadlineReached(void)
{
    timer_deadline_reached_IgnoreAndReturn(true);
    led_toggle_Expect();

    superloop_run();
}

#endif // TEST
