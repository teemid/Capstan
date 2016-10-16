#ifndef CAPSTAN_MATH_COMMON_H
#define CAPSTAN_MATH_COMMON_H


#include "Capstan/Common.h"


namespace Capstan
{
namespace Math
{
    inline UInt8 Abs (Int8 i)
    {
        return (i < 0) ? (-1) * i : i;
    }

    inline UInt16 Abs (Int16 i)
    {
        return (i < 0) ? (-1) * i : i;
    }

    inline UInt32 Abs (Int32 i)
    {
        return (i < 0) ? (-1) * i : i;
    }

    inline UInt64 Abs (Int64 i)
    {
        return (i < 0) ? (-1) * i : i;
    }
}
}


#endif
