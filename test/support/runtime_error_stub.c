#include "runtime_error_stub.h"

static const char * message = "No Error";

void runtime_error_stub_reset(void)
{
    message = "No Error!";
}

const char * runtime_error_stub_get_last_error(void)
{
    return message;
}

void runtime_error_failed(const char *msg)
{
    message = msg;
}
