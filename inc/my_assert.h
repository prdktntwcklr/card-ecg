#ifndef MY_ASSERT_H
#define MY_ASSERT_H

void my_assert_failed(const char *file, int line);

#ifdef NASSERT /* NASSERT defined -- asserts disabled */

#define MY_ASSERT(ignore) ((void)0U)

#else /* NASSERT not defined -- asserts enabled */

/**
 * @brief Used for runtime asserts.
 *
 * @ref   https://barrgroup.com/embedded-systems/how-to/design-by-contract-for-embedded-software
 */
#define MY_ASSERT(expr)                                                        \
    do                                                                         \
    {                                                                          \
        if(expr)                                                               \
        {                                                                      \
        }                                                                      \
        else                                                                   \
        {                                                                      \
            my_assert_failed(__FILE__, __LINE__);                              \
        }                                                                      \
    } while(0)

#endif /* NASSERT */

#define MY_ERROR() MY_ASSERT(0)

#define UNUSED(x) ((void)(x))
/**
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

#endif /* MY_ASSERT_H */
/*** end of file ***/
