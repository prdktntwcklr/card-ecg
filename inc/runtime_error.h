#ifndef RUNTIME_ERROR_H
#define RUNTIME_ERROR_H

void runtime_error_failed(const char *msg);

#define RUNTIME_ERROR(msg) \
    runtime_error_failed(msg)

#endif // RUNTIME_ERROR_H
