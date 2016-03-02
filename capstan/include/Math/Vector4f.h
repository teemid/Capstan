#ifndef CAPSTAN_MATH_VECTOR4_H
#define CAPSTAN_MATH_VECTOR4_H


#include "Math/Vector.h"
#include "Platform/Memory.h"


namespace Capstan
{
    template<>
    struct Vector<Real32, 4>
    {
        union {
            Real32 data[4];
            struct { Real32 x, y, z, w; };
        };

        Vector (void);
        Vector (Real32 x);
        Vector (Real32 x, Real32 y, Real32 z, Real32 w);

        Vector4f operator +(const Vector4f & rhs);
        Vector4f operator -(const Vector4f & rhs);
        Vector4f operator *(const Vector4f & rhs);

        Real32 & operator [](UInt32 index);
        Bool32 operator ==(const Vector4f & rhs);
    };

    //==== Implementation begin ====//
    Vector<Real32, 4>::Vector (void)
    {
        Memory::Zero(data, sizeof(Real32) * 4);
    }

    Vector<Real32, 4>::Vector (Real32 x) : x(x), y(x), z(x), w(x) { }

    Vector<Real32, 4>::Vector (Real32 x, Real32 y, Real32 z, Real32 w) //: x(x), y(y), z(z), w(w) { };
    {
        x = x;
        y = y;
        z = z;
        w = w;
    }

    Real32 & Vector<Real32, 4>::operator [] (UInt32 index)
    {
        return data[index];
    }

    Vector4f Vector<Real32, 4>::operator +(const Vector4f & rhs)
    {
        Vector4f result = {
            x + rhs.x,
            y + rhs.y,
            z + rhs.z,
            w + rhs.w
        };

        return result;
    }

    Vector4f Vector<Real32, 4>::operator -(const Vector4f & rhs)
    {
        Vector4f result = {
            x - rhs.x,
            y - rhs.y,
            z - rhs.z,
            w - rhs.w
        };

        return result;
    }

    Vector4f Vector<Real32, 4>::operator *(const Vector4f & rhs)
    {
        Vector4f result = {
            x * rhs.x,
            y * rhs.y,
            z * rhs.z,
            w * rhs.w
        };

        return result;
    }
    //==== Implementation end ====//
}


#endif
