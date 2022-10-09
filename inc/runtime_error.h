#ifndef RUNTIME_ERROR_H
#define RUNTIME_ERROR_H

void runtime_error(const char *msg);

/*
 * @brief Generates runtime asserts. Unit test-friendly.
 */
#define RUNTIME_ERROR(msg)        \
    do                            \
    {                             \
        runtime_error(msg);       \
    } while (0)

/*
 * @brief Generates a static assert.
 *
 * @ref   https://stackoverflow.com/questions/3385515/static-assert-in-c
 */
#ifndef TEST
#define CTASTR2(pre,post) pre ## post
#define CTASTR(pre,post) CTASTR2(pre,post)
#define STATIC_ASSERT(cond,msg)                                             \
    typedef struct { int CTASTR(static_assertion_failed_,msg) : !!(cond); } \
        CTASTR(static_assertion_failed_,__COUNTER__)
#else
#define STATIC_ASSERT(cond,msg)
#endif

#endif // RUNTIME_ERROR_H
