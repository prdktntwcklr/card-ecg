#ifdef TEST

#include "unity.h"

#define EXTERN

#include "testable_mcu_registers.h"

#include "display.h"
#include "display_drv.h"
#include "mock_spi.h"
#include "mock_timer.h"
#include "my_assert_stub.h"

void test_display_send_framebuffer_should_throwErrorIfNullPointerReceived(void)
{
    uint8_t *ptr = NULL;

    TEST_ASSERT_FAIL_ASSERT(display_send_framebuffer(ptr));
}

#endif // TEST
