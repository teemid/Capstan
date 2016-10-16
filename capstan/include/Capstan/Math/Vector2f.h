#ifndef CAPSTAN_MATH_VECTOR2F_H
#define CAPSTAN_MATH_VECTOR2F_H

#include "Capstan/Platform/Intrinsics.h"
#include "Capstan/Types.h"


namespace Capstan
{
    struct Vector2f
    {
        union {
            Real32 data[2];
            struct { Real32 x, y; };
            struct { Real32 u, v; };
        };

        Vector2f (void);
        Vector2f (Real32 x);
        Vector2f (Real32 x, Real32 y);

        inline Vector2f operator +(const Vector2f & rhs);
        inline Vector2f operator -(const Vector2f & rhs);
        inline Vector2f operator *(const Vector2f & rhs);
        inline Vector2f operator /(const Vector2f & rhs);

        inline Vector2f operator +(const Real32 & scalar);
        inline Vector2f operator -(const Real32 & scalar);
        inline Vector2f operator *(const Real32 & scalar);
        inline Vector2f operator /(const Real32 & scalar);

        inline Bool32 operator ==(const Vector2f & rhs);
    };

    inline Vector2f Normalize     (Vector2f & v);
    inline Real32   LengthSquared (Vector2f & v);
    inline Real32   Length        (Vector2f & v);
    inline Real32   Dot           (Vector2f & v1, Vector2f & v2);
    inline Real32   Angle         (Vector2f & v1, Vector2f & v2);
    inline Vector2f Lerp          (Vector2f & start, Vector2f & end, Real32 t);

    //==== Implementation begin ====//
    inline Vector2f Vector2f::operator +(const Vector2f & rhs)
    {
        Vector2f v;

        v.x = x + rhs.x;
        v.y = y + rhs.y;

        return v;
    }

    inline Vector2f Vector2f::operator -(const Vector2f & rhs)
    {
        Vector2f v;

        v.x = x - rhs.x;
        v.y = y - rhs.y;

        return v;
    }

    inline Vector2f Vector2f::operator *(const Vector2f & rhs)
    {
        Vector2f v;

        v.x = x * rhs.x;
        v.y = y * rhs.y;

        return v;
    }

    inline Vector2f Vector2f::operator /(const Vector2f & rhs)
    {
        Vector2f v;

        v.x = x / rhs.x;
        v.y = y / rhs.y;

        return v;
    }

    inline Bool32 Vector2f::operator ==(const Vector2f & rhs)
    {
        return (x == rhs.x && y == rhs.y);
    }

    inline Vector2f Vector2f::operator +(const Real32 & scalar)
    {
        return Vector2f(x + scalar, y + scalar);
    }

    inline Vector2f Vector2f::operator -(const Real32 & scalar)
    {
        return Vector2f(x - scalar, y - scalar);
    }

    inline Vector2f Vector2f::operator *(const Real32 & scalar)
    {
        return Vector2f(x * scalar, y * scalar);
    }

    inline Vector2f Vector2f::operator /(const Real32 & scalar)
    {
        return Vector2f(x / scalar, y / scalar);
    }

    inline Real32 LengthSquared (Vector2f & v)
    {
        return v.x * v.x + v.y * v.y;
    }

    inline Real32 Length (Vector2f & v)
    {
        return SquareRoot(LengthSquared(v));
    }

    inline Vector2f Normalize (Vector2f & v)
    {
        return v / Length(v);
    }

    inline Real32 Dot (Vector2f & v1, Vector2f & v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    inline Real32 Angle (Vector2f & v1, Vector2f & v2)
    {
        return Cos(Dot(v1, v2) / Length(v1) * Length(v2));
    }

    inline Vector2f Lerp (Vector2f & start, Vector2f & end, Real32 t)
    {
        return start * (1.0f - t) + end * t;
    }
    //==== Implementation end ====//
}

#endif
