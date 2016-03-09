#ifndef CAPSTAN_MATH_VECTOR4_H
#define CAPSTAN_MATH_VECTOR4_H

#include "Platform/Memory.h"
#include "Platform/Intrinsics.h"

// NOTE (Emil): This file is included at the bottom of Vector.h.

typedef Vector4f Color4f;

template<>
struct Capstan::Vector<Real32, 4>
{
    union {
        Real32 data[4];
        struct { Real32 x, y, z, w; };
        struct { Real32 r, g, b, a; };
    };

    Vector (void);
    Vector (Real32 x);
    Vector (Real32 x, Real32 y, Real32 z);
    Vector (Real32 x, Real32 y, Real32 z, Real32 w);

    Vector4f operator +(const Vector4f & rhs);
    Vector4f operator -(const Vector4f & rhs);
    Vector4f operator *(const Vector4f & rhs);

    Vector4f operator +(const Real32 & scalar);
    Vector4f operator -(const Real32 & scalar);
    Vector4f operator *(const Real32 & scalar);
    Vector4f operator /(const Real32 & scalar);

    Vector4f operator -(void);
    Real32 & operator [](UInt32 index);
    Bool32 operator ==(const Vector4f & rhs);
};


// NOTE (Emil): Should this return LengthSquare with or without w component?
template<>
inline Real32 LengthSquared (Vector4f & v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

template<>
inline Real32 Length (Vector4f & v)
{
    return SquareRoot(LengthSquared(v));
}

template<>
inline Vector4f Normalize (Vector4f & v)
{
    auto length = Length(v);

    return (v * (1 / length));
}

template<>
inline Real32 Dot (Vector4f & v1, Vector4f & v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w + v2.w;
}

//==== Implementation begin ====//
Vector4f::Vector (void)
{
    Memory::Zero(data, sizeof(Real32) * 4);
}

Vector4f::Vector (Real32 x) : x(x), y(x), z(x), w(x) { }

Vector4f::Vector (Real32 x, Real32 y, Real32 z) : x(x), y(y), z(z) { }

Vector4f::Vector (Real32 x, Real32 y, Real32 z, Real32 w) : x(x), y(y), z(z), w(w) { };


Vector4f Vector4f::operator -(void)
{
    return Vector4f(-x, -y, -z, -w);
}


Real32 & Vector4f::operator [] (UInt32 index)
{
    return data[index];
}

Vector4f Vector4f::operator +(const Vector4f & rhs)
{
    return Vector4f(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

Vector4f Vector4f::operator -(const Vector4f & rhs)
{
    return Vector4f(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

Vector4f Vector4f::operator *(const Vector4f & rhs)
{
    return Vector4f(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
}

Vector4f Vector4f::operator +(const Real32 & scalar)
{
    return Vector4f(x + scalar, y + scalar, z + scalar, w + scalar);
}

Vector4f Vector4f::operator -(const Real32 & scalar)
{
    return Vector4f(x - scalar, y - scalar, z - scalar, w - scalar);
}

Vector4f Vector4f::operator *(const Real32 & scalar)
{
    return Vector4f(x * scalar, y * scalar, z * scalar, w * scalar);
}

Vector4f Vector4f::operator /(const Real32 & scalar)
{
    return Vector4f(x / scalar, y / scalar, z / scalar, w / scalar);
}
//==== Implementation end ====//


#endif
