#ifndef CAPSTAN_ASSERT_H
#define CAPSTAN_ASSERT_H


#ifdef _WIN32

#include <intrin.h>

#define HALT() __debugbreak()

#else

#define HALT() __asm { int 3 }

#endif END #ifdef _WIN32


#ifdef CAPSTAN_ASSERT

namespace Capstan
{
    void ReportAssertFailure (char * msg, char * filename, int linenumber);
}

#include <cstdlib>
#include <cstdio>

#define Assert(expression, message, ...) \
    if (!expression) \
    { \
        printf("Expression: %s failed at %s: %i", #expression, __FILE__, __LINE__); \
        printf(message, __VA_ARGS__); \
        \
        HALT(); \
    } \
    else { }

#else

#define assert(expr)

#endif // END #ifdef CAPSTAN_ASSERT

#endif // CAPSTAN_ASSERT_H
