#ifdef TEST

#include "unity.h"

#define EXTERN

#include "testable_mcu_registers.h"

#include "my_assert_stub.h"
#include "ring_buffer.h"
#include "uart.c" /* hack to test static functions */
#include "uart.h"
#include "uart_drv.h"

void setUp(void)
{
}

void tearDown(void)
{
}

#endif // TEST
