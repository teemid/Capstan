#ifndef CAPSTAN_MATH_VECTOR3F_H
#define CAPSTAN_MATH_VECTOR3F_H


#include "Platform/Intrinsics.h"
#include "Platform/Types.h"

#include "Math/Vector2f.h"

namespace Capstan
{
    struct Vector3f
    {
        union {
            Real32 data[3];
            struct { Real32 x, y, z; };
            struct { Real32 r, g, b; };
        };

        Vector3f (void);
        Vector3f (Real32 x);
        Vector3f (Real32 x, Real32 y, Real32 z);

        Vector3f (Vector2f & v);
        Vector3f (Vector2f & v, Real32 f);

        Vector3f operator +(const Vector3f & rhs);
        Vector3f operator -(const Vector3f & rhs);
        Vector3f operator *(const Vector3f & rhs);
        Vector3f operator /(const Vector3f & rhs);

        Vector3f operator +(const Real32 & scalar);
        Vector3f operator -(const Real32 & scalar);
        Vector3f operator *(const Real32 & scalar);
        Vector3f operator /(const Real32 & scalar);

        Vector3f operator -(void);
        Bool32 operator ==(const Vector3f & rhs);
    };

    inline Real32 LengthSquared (Vector3f & v);

    inline Real32 Length (Vector3f & v);

    inline Vector3f Normalize (Vector3f & v);

    inline Vector3f Cross (Vector3f & v1, Vector3f & v2);

    inline Real32 Dot (Vector3f & v1, Vector3f & v2);

    inline Real32 Angle (Vector3f & v1, Vector3f & v2);

    inline Vector3f Lerp (Vector3f & start, Vector3f & end, Real32 t);

    //==== Implementation begin ====//
    Vector3f::Vector3f (void) : x(0), y(0), z(0) { };

    Vector3f::Vector3f (Real32 x) : x(x) { };

    Vector3f::Vector3f (Real32 x, Real32 y, Real32 z) : x(x), y(y), z(z) { };

    Vector3f::Vector3f (Vector2f & v) : x(v.x), y(v.y), z(0.0f) { };

    Vector3f::Vector3f (Vector2f & v, Real32 f) : x(v.x), y(v.y), z(f) { };

    Vector3f Vector3f::operator +(const Vector3f & rhs)
    {
        Vector3f v;

        v.x = x + rhs.x;
        v.y = y + rhs.y;
        v.z = y + rhs.z;

        return v;
    };

    Vector3f Vector3f::operator -(const Vector3f & rhs)
    {
        Vector3f v;

        v.x = x - rhs.x;
        v.y = y - rhs.y;
        v.z = z - rhs.z;

        return v;
    };

    Vector3f Vector3f::operator *(const Vector3f & rhs)
    {
        Vector3f v;

        v.x = x * rhs.x;
        v.y = y * rhs.y;
        v.z = z * rhs.z;

        return v;
    };

    Vector3f Vector3f::operator /(const Vector3f & rhs)
    {
        Vector3f v;

        v.x = x / rhs.x;
        v.y = y / rhs.y;
        v.z = z / rhs.z;

        return v;
    };

    Vector3f Vector3f::operator +(const Real32 & scalar)
    {
        return Vector3f(x + scalar, y + scalar, z + scalar);
    }

    Vector3f Vector3f::operator -(const Real32 & scalar)
    {
        return Vector3f(x - scalar, y - scalar, z - scalar);
    }

    Vector3f Vector3f::operator *(const Real32 & scalar)
    {
        return Vector3f(x * scalar, y * scalar, z * scalar);
    }

    Vector3f Vector3f::operator /(const Real32 & scalar)
    {
        return Vector3f(x / scalar, y / scalar, z / scalar);
    }

    Vector3f Vector3f::operator -(void)
    {
        return Vector3f(-x, -y, -z);
    }

    Bool32 Vector3f::operator ==(const Vector3f & rhs)
    {
        return (x == rhs.x && y == rhs.y && z == rhs.z);
    };

    inline Real32 LengthSquared (Vector3f & v)
    {
        return v.x * v.x + v.y * v.y;
    }

    inline Real32 Length (Vector3f & v)
    {
        return SquareRoot(LengthSquared(v));
    }

    inline Vector3f Normalize (Vector3f & v)
    {
        return v / Length(v);
    }

    inline Vector3f Cross (Vector3f & v1, Vector3f & v2)
    {
        return Vector3f(
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x
        );
    }

    inline Real32 Dot (Vector3f & v1, Vector3f & v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    inline Real32 Angle (Vector3f & v1, Vector3f & v2)
    {
        return Cos(Dot(v1, v2) / Length(v1) * Length(v2));
    }

    inline Vector3f Lerp (Vector3f & start, Vector3f & end, Real32 t)
    {
        return start * (1.0f - t) + end * t;
    }
    //==== Implementation end ====//
}

#endif
