#include "my_assert.h"
#include "display.h"
#include "framebuffer.h"

void my_assert_failed(const char *file, int line)
{
    /* TODO: output string to screen or uart */
    UNUSED(file);
    UNUSED(line);

    /* hang in while loop */
    while(1) {}
}
