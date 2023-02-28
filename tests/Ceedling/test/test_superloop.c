#ifdef TEST

#include "unity.h"

#define EXTERN 

#include "testable_mcu_registers.h"

#include "logo.h"
#include "mock_adc.h"
#include "mock_dac.h"
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

void test_superloop_run_should_notDoAnythingIfDeadlineNotReached(void)
{
    timer_deadline_reached_IgnoreAndReturn(false);
    
    superloop_run();
}

#endif // TEST
