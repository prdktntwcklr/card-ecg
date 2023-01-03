#include "my_assert_stub.h"

void my_assert_failed(const char *file, int line)
{
    Throw(0);
}
