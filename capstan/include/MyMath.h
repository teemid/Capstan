#ifndef CAPSTAN_MATH_H
#define CAPSTAN_MATH_H


#include "Platform/Types.h"


namespace Capstan
{
namespace Math
{
    inline Int32 Abs (Int32 i)
    {
        return (i < 0 ? -i : i);
    }

    inline Real32 Abs (Real32 f)
    {
        return (f < 0 ? -f : f);
    }

    inline Real64 Abs (Real64 f)
    {
        return (f < 0 ? -f : f);
    }

    inline Real32 Sin (Real32 angle)
    {

    }

    inline Real32 Cos (Real32 angle)
    {

    }

    inline Real32 Tan (Real32 angle)
    {

    }
}
}

#endif
