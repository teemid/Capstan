#ifndef CAPSTAN_MATH_VECTOR4F_H
#define CAPSTAN_MATH_VECTOR4F_H

#include "Capstan/Platform/Memory.h"
#include "Capstan/Platform/Intrinsics.h"


namespace Capstan
{
    struct Vector4f
    {
        union {
            Real32 data[4];
            struct { Real32 x, y, z, w; };
            struct { Real32 r, g, b, a; };
        };

        Vector4f (void);
        Vector4f (Real32 x);
        Vector4f (Real32 x, Real32 y, Real32 z);
        Vector4f (Real32 x, Real32 y, Real32 z, Real32 w);

        inline Vector4f operator +(const Vector4f & rhs);
        inline Vector4f operator -(const Vector4f & rhs);
        inline Vector4f operator *(const Vector4f & rhs);

        inline Vector4f operator +(const Real32 & scalar);
        inline Vector4f operator -(const Real32 & scalar);
        inline Vector4f operator *(const Real32 & scalar);
        inline Vector4f operator /(const Real32 & scalar);

        inline Vector4f operator -(void);
        inline Real32 & operator [](UInt32 index);
        inline Bool32 operator ==(const Vector4f & rhs);
    };

    inline Real32 LengthSquared (Vector4f & v);

    inline Real32 Length (Vector4f & v);

    inline Vector4f Normalize (Vector4f & v);

    inline Real32 Dot (Vector4f & v1, Vector4f & v2);

    //==== Implementation begin ====//
    inline Vector4f Vector4f::operator -(void)
    {
        return Vector4f(-x, -y, -z, -w);
    }

    inline Real32 & Vector4f::operator [] (UInt32 index)
    {
        return data[index];
    }

    inline Vector4f Vector4f::operator +(const Vector4f & rhs)
    {
        return Vector4f(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
    }

    inline Vector4f Vector4f::operator -(const Vector4f & rhs)
    {
        return Vector4f(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
    }

    inline Vector4f Vector4f::operator *(const Vector4f & rhs)
    {
        return Vector4f(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
    }

    inline Vector4f Vector4f::operator +(const Real32 & scalar)
    {
        return Vector4f(x + scalar, y + scalar, z + scalar, w + scalar);
    }

    inline Vector4f Vector4f::operator -(const Real32 & scalar)
    {
        return Vector4f(x - scalar, y - scalar, z - scalar, w - scalar);
    }

    inline Vector4f Vector4f::operator *(const Real32 & scalar)
    {
        return Vector4f(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    inline Vector4f Vector4f::operator /(const Real32 & scalar)
    {
        return Vector4f(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    inline Real32 LengthSquared (Vector4f & v)
    {
        return v.x * v.x + v.y * v.y + v.z * v.z;
    }

    inline Real32 Length (Vector4f & v)
    {
        return SquareRoot(LengthSquared(v));
    }

    inline Vector4f Normalize (Vector4f & v)
    {
        auto length = Length(v);

        return (v * (1 / length));
    }

    inline Real32 Dot (Vector4f & v1, Vector4f & v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w + v2.w;
    }
    //==== Implementation end ====//
}

#endif
