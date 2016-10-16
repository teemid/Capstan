#ifndef CAPSTAN_MATH_QUATERNION_H
#define CAPSTAN_MATH_QUATERNION_H

#include "Math/Vector.h"


namespace Capstan
{
    struct Quaternion
    {
        union
        {
            Real32 data[3];
            struct
            {
                Real32 i;
                Real32 j;
                Real32 k;
            };
        };

        Quaternion (void);
        Quaternion (Real32 i, Real32 j, Real32 k);

        Quaternion operator +(const Quaternion & rhs);
        Quaternion operator -(const Quaternion & rhs);
        Quaternion operator *(const Quaternion & rhs);
        Quaternion operator /(const Quaternion & rhs);

        Quaternion operator +(const T scalar);
        Quaternion operator -(const T scalar);
        Quaternion operator *(const T scalar);
        Quaternion operator /(const T scalar);

        T operator[](UInt32 index);

        Bool32 operator ==(const Quaternion & rhs);
    };
}

#endif
