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


#define assert(expr) \
        if (expr) {} \
        else \
        { \
            Capstan::ReportAssertFailure(#expr, __FILE__, __LINE__); \
            HALT(); \
        }

#else

#define assert(expr)

#endif // END #ifdef CAPSTAN_ASSERT

#endif // CAPSTAN_ASSERT_H
