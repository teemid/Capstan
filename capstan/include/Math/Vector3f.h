#ifndef CAPSTAN_MATH_VECTOR3_H
#define CAPSTAN_MATH_VECTOR3_H

// NOTE (Emil): This file is included at the bottom of Vector.h.

typedef Vector3f Color3f;

template<>
struct Vector<Real32, 3>
{
    union {
        Real32 data[3];
        struct { Real32 x, y, z; };
        struct { Real32 r, g, b; };
    };

    Vector (void);
    Vector (Real32 x);
    Vector (Real32 x, Real32 y, Real32 z);

    Vector (Vector2f & v);
    Vector (Vector2f & v, Real32 f);

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

template<>
inline Real32 LengthSquared (Vector3f & v);

template<>
inline Real32 Length (Vector3f & v);

template<>
inline Vector3f Normalize (Vector3f & v);

template<>
inline Vector3f Cross (Vector3f & v1, Vector3f & v2);

template<>
inline Real32 Dot (Vector3f & v1, Vector3f & v2);

template<>
inline Real32 Angle (Vector3f & v1, Vector3f & v2);

template <>
inline Vector3f Lerp (Vector3f & start, Vector3f & end, Real32 t);

//==== Implementation begin ====//
Vector3f::Vector (void) : x(0), y(0), z(0) { };

Vector3f::Vector (Real32 x) : x(x) { };

Vector3f::Vector (Real32 x, Real32 y, Real32 z) : x(x), y(y), z(z) { };

Vector3f::Vector (Vector2f & v)
{
    Vector3f result;
    result.x = v.x;
    result.y = v.y;
    result.z = 0.0f;
}

Vector3f::Vector (Vector2f & v, Real32 f)
{
    Vector3f result;
    result.x = v.x;
    result.y = v.y;
    result.z = f;
}

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

template<>
inline Real32 LengthSquared (Vector3f & v)
{
    return v.x * v.x + v.y * v.y;
}

template<>
inline Real32 Length (Vector3f & v)
{
    return SquareRoot(LengthSquared(v));
}

template<>
inline Vector3f Normalize (Vector3f & v)
{
    return v / Length(v);
}

template<>
inline Vector3f Cross (Vector3f & v1, Vector3f & v2)
{
    return Vector2f();
}

template<>
inline Real32 Dot (Vector3f & v1, Vector3f & v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

template<>
inline Real32 Angle (Vector3f & v1, Vector3f & v2)
{
    return Cos(Dot(v1, v2) / Length(v1) * Length(v2));
}

template <>
inline Vector3f Lerp (Vector3f & start, Vector3f & end, Real32 t)
{
    return start * (1.0f - t) + end * t;
}
//==== Implementation end ====//

#endif
