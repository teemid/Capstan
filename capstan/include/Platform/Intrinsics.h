#ifndef CAPSTAN_PLATFORM_INTRINSICS
#define CAPSTAN_PLATFORM_INTRINSICS

#if defined(_MSC_VER)
#include <intrin.h>
#endif

#include <math.h>

namespace Capstan
{
    inline Real32 Sin(Real32 angle)
    {
       return sinf(angle);
    }

    inline Real32 Cos(Real32 angle)
    {
        return cosf(angle);
    }
}


#endif
