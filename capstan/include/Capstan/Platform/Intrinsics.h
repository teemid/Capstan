#ifndef CAPSTAN_PLATFORM_INTRINSICS
#define CAPSTAN_PLATFORM_INTRINSICS

#if defined(_MSC_VER)
#include <intrin.h>
#endif

#include <cmath>

#include "Capstan/Types.h"


namespace Capstan
{
    inline Real32 Sin (Real32 angle)
    {
       return sinf(angle);
    }

    inline Real32 Cos (Real32 angle)
    {
        return cosf(angle);
    }

    inline Real32 Tan (Real32 angle)
    {
        return tanf(angle);
    }

    inline Real32 Atan2 (Real32 r1, Real32 r2)
    {
        return atan2f(r1, r2);
    }

    inline Real32 SquareRoot (Real32 r)
    {
        return sqrtf(r);
    }

    inline Real32 Power(Real32 base, Real32 exponent)
    {
        return powf(base, exponent);
    }

    inline Real32 Ln (Real32 r)
    {
        return logf(r);
    }

    inline Real32 Log (Real32 r)
    {
        return log10f(r);
    }

    inline Real32 Exponential (Real32 r)
    {
        return expf(r);
    }
}


#endif
