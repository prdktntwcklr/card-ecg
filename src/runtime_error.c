#include "runtime_error.h"

void runtime_error(const char *msg)
{
    /* TODO: output error message to screen */
    /* do not have access to framebuffer handler from here */

    /* hang in while loop */
    while(1) {}
}
