#ifdef TEST

#include "unity.h"

#define EXTERN 

#include "testable_mcu_registers.h"
#include "timer.h"
#include "timer.c" /* hack to test static functions */
#include "runtime_error_stub.h"

void setUp(void)
{
    T0LD = 0;
    T0CON = 0;
    IRQEN = 0;

    timer_set_stamp(0);
}

void tearDown(void)
{
    timer_deinit();
}

void test_timer_init_should_initializeTimerRegistersCorrectly(void)
{
    timer_init();

    TEST_ASSERT_EQUAL(400, T0LD);
    TEST_ASSERT_EQUAL_HEX32(0x000004C8, T0CON);
    TEST_ASSERT_EQUAL_HEX32(0x00000008, IRQEN);    
}

void test_timer_increment_stamp_should_incrementTimeStampCorrectly(void)
{
    TEST_ASSERT_EQUAL(0, timer_get_stamp());
    
    timer_increment_stamp(50);
    TEST_ASSERT_EQUAL(50, timer_get_stamp());

    timer_increment_stamp(100);
    TEST_ASSERT_EQUAL(150, timer_get_stamp());

    timer_increment_stamp(2300);
    TEST_ASSERT_EQUAL(2450, timer_get_stamp());   
}

void test_timer_handle_interrupt_should_incrementReloadTimerAndTimeStamp(void)
{
    TEST_ASSERT_EQUAL(0, T0LD);
    TEST_ASSERT_EQUAL(0, timer_get_stamp());

    timer_handle_interrupt();
    TEST_ASSERT_EQUAL(400, T0LD);
    TEST_ASSERT_EQUAL(10, timer_get_stamp());
}

void test_timer_set_stamp_should_SetTimeStampCorrectly(void)
{
    TEST_ASSERT_EQUAL(0, timer_get_stamp());

    timer_set_stamp(50);
    TEST_ASSERT_EQUAL(50, timer_get_stamp());

    timer_set_stamp(3200);
    TEST_ASSERT_EQUAL(3200, timer_get_stamp());

    timer_set_stamp(70);
    TEST_ASSERT_EQUAL(70, timer_get_stamp());     
}

void test_timer_deadline_reached_should_handleDeadlinesCorrectly(void)
{
    timer_init();

    timer_set_stamp(0);
    TEST_ASSERT_FALSE(timer_deadline_reached(50));

    timer_increment_stamp(100);
    TEST_ASSERT_TRUE(timer_deadline_reached(50));

    timer_increment_stamp(100);
    TEST_ASSERT_TRUE(timer_deadline_reached(200));

    /* test if rollover is handled correctly */
    timer_set_stamp(4294967290);
    TEST_ASSERT_FALSE(timer_deadline_reached(50));

    timer_increment_stamp(100);
    TEST_ASSERT_TRUE(timer_deadline_reached(50));
}

void test_deadline_reached_should_throwErrorIfTimerIsNotInitialized(void)
{
    timer_deadline_reached(1000);

    TEST_ASSERT_EQUAL_STRING("Timer is not initialized!", runtime_error_stub_get_last_error());
}

#endif // TEST
