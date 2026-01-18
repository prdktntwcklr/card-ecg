#ifndef NPRINTF /* NPRINTF not defined -- printf enabled */

#include "printf/printf.h"

#define MY_PRINTF(...) printf_(__VA_ARGS__)

#else /* NPRINTF defined -- printf disabled */

#define MY_PRINTF(...) ((void)0U)

#endif /* NPRINTF */
/*** end of file ***/
