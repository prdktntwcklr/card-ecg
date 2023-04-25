#ifndef MY_ASSERT_STUB_H
#define MY_ASSERT_STUB_H

#include "CException.h"
#include "unity.h"

#define TEST_ASSERT_FAIL_ASSERT(code_under_test)                               \
    {                                                                          \
        CEXCEPTION_T e;                                                        \
        Try                                                                    \
        {                                                                      \
            code_under_test;                                                   \
            TEST_FAIL_MESSAGE("Code under test did not assert!");              \
        }                                                                      \
        Catch(e) {}                                                            \
    }

#endif // MY_ASSERT_STUB_H
