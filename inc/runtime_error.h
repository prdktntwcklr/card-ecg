#ifndef RUNTIME_ERROR_H
#define RUNTIME_ERROR_H

void runtime_error(const char *msg);

#define RUNTIME_ERROR(msg)        \
    do                            \
    {                             \
        runtime_error(msg);       \
        return;                   \
    } while (0)

#endif // RUNTIME_ERROR_H
