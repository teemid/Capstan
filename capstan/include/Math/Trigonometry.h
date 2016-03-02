#ifndef CAPSTAN_MATH_TRIGONOMETRIC_H
#define CAPSTAN_MATH_TRIGONOMETRIC_H


#include "Math/Constants.h"
#include "Platform/Types.h"


namespace Capstan
{
    inline Real32 Sin (Real32 radians)
    {

    }

    inline Real32 Cos (Real32 radians)
    {

    }

    inline Real32 Tan (Real32 radians)
    {

    }

    inline Real32 Atan2 (Real32 x, Real32 y)
    {

    }

    inline Real32 ToRadians (Real32 degrees)
    {
        return (degrees / 360.0f) * TWO_PI;
    }

    inline Real32 ToDegrees (Real32 radians)
    {
        return (radians / TWO_PI) * 360.0f;
    }
}


#endif
