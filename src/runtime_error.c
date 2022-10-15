#include "runtime_error.h"
#include "display.h"
#include "framebuffer.h"

void runtime_error(const char *msg)
{
    /* output error message to screen, assumes framebuffer is initialized */
    fb_handle_t fb = framebuffer_get();
    framebuffer_clear(fb);
    framebuffer_draw_string(fb, 0, 0, msg);
    display_send_framebuffer(fb);

    /* hang in while loop */
    while(1) {}
}
