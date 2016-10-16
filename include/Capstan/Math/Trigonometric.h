#ifndef CAPSTAN_MATH_TRIGONOMETRIC_H
#define CAPSTAN_MATH_TRIGONOMETRIC_H


#include "Math/Constants.h"
#include "Platform/Types.h"


namespace Capstan
{
namespace Math
{
    inline Real32 ToRadians (Real32 degrees)
    {
        return (degrees / 360.0f) * TWO_PI;
    }

    inline Real32 ToDegrees (Real32 radians)
    {
        return (radians / TWO_PI) * 360.0f;
    }
}
}

#endif
