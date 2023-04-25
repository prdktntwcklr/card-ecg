#ifdef TEST

#include "unity.h"

#define EXTERN

#include "system.h"
#include "testable_mcu_registers.h"

void setUp(void)
{
    POWKEY1 = 0;
    POWCON0 = 0;
    POWKEY2 = 0;
}

void tearDown(void) {}

void test_system_init_should_initializeSystemRegistersCorrectly(void)
{
    system_init();

    TEST_ASSERT_EQUAL_HEX16(0x0001, POWKEY1);
    TEST_ASSERT_EQUAL_HEX8(0x38, POWCON0);
    TEST_ASSERT_EQUAL_HEX16(0x00F4, POWKEY2);
}

#endif // TEST
