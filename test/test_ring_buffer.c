#ifdef TEST

#include "unity.h"

#define EXTERN 

#include "ring_buffer.h"

void setUp(void)
{
    ring_buffer_reset();
}

void tearDown(void)
{
}

void test_ring_buffer_should_defaultToEmpty(void)
{
    TEST_ASSERT_TRUE(ring_buffer_is_empty());
}

void test_ring_buffer_should_notReturnDataIfEmpty(void)
{
    TEST_ASSERT_TRUE(ring_buffer_is_empty());

    uint8_t byte = 0; // byte to hold the data from the ring buffer

    TEST_ASSERT_FALSE(ring_buffer_get(&byte));
}

void test_ring_buffer_should_noLongerBeEmptyAfterPut(void)
{
    TEST_ASSERT_TRUE(ring_buffer_put('A'));
    TEST_ASSERT_FALSE(ring_buffer_is_empty());
}

void test_ring_buffer_should_getBackCorrectDataAfterPut(void)
{
    ring_buffer_put('A');
    ring_buffer_put('b');
    ring_buffer_put('C');
    
    uint8_t byte = 0; // byte to hold the data from the ring buffer

    TEST_ASSERT_TRUE(ring_buffer_get(&byte));
    TEST_ASSERT_EQUAL('A', byte);

    TEST_ASSERT_TRUE(ring_buffer_get(&byte));
    TEST_ASSERT_EQUAL('b', byte);

    TEST_ASSERT_TRUE(ring_buffer_get(&byte));
    TEST_ASSERT_EQUAL('C', byte);

    TEST_ASSERT_TRUE(ring_buffer_is_empty());
}

void test_ring_buffer_should_signalFullCorrectly(void)
{
    for(uint8_t i = 0; i < 62; i++)
    {
        TEST_ASSERT_TRUE(ring_buffer_put(i));
        TEST_ASSERT_FALSE(ring_buffer_is_full());
    }

    TEST_ASSERT_TRUE(ring_buffer_put(62));
    TEST_ASSERT_TRUE(ring_buffer_is_full());

    TEST_ASSERT_FALSE(ring_buffer_put(63));
}

#endif // TEST
