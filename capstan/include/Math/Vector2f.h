#ifndef CAPSTAN_MATH_VECTOR2_H
#define CAPSTAN_MATH_VECTOR2_H

// NOTE (Emil): This file is included at the bottom of Vector.h.


template<>
struct Vector<Real32, 2>
{
    union {
        Real32 data[2];
        struct { Real32 x, y; };
        struct { Real32 u, v; };
    };

    Vector (void);
    Vector (Real32 x);
    Vector (Real32 x, Real32 y);

    Vector2f operator +(const Vector2f & rhs);
    Vector2f operator -(const Vector2f & rhs);
    Vector2f operator *(const Vector2f & rhs);
    Vector2f operator /(const Vector2f & rhs);

    Vector2f operator +(const Real32 & scalar);
    Vector2f operator -(const Real32 & scalar);
    Vector2f operator *(const Real32 & scalar);
    Vector2f operator /(const Real32 & scalar);

    Bool32 operator ==(const Vector2f & rhs);
};

template<>
inline Vector2f Normalize (Vector2f & v);

template<>
inline Real32 LengthSquared (Vector2f & v);

template<>
inline Real32 Length (Vector2f & v);

template<>
inline Vector2f Cross (Vector2f & v1, Vector2f & v2);

template<>
inline Real32 Dot (Vector2f & v1, Vector2f & v2);

template<>
inline Real32 Angle (Vector2f & v1, Vector2f & v2);

template <>
inline Vector2f Lerp (Vector2f & start, Vector2f & end, Real32 t);

//==== Implementation begin ====//
Vector2f::Vector (void) : x(0), y(0) { };

Vector2f::Vector (Real32 x) : x(x), y(x) { };

Vector2f::Vector (Real32 x, Real32 y) : x(x), y(y) { };

Vector2f Vector2f::operator +(const Vector2f & rhs)
{
    Vector2f v;

    v.x = x + rhs.x;
    v.y = y + rhs.y;

    return v;
};

Vector2f Vector2f::operator -(const Vector2f & rhs)
{
    Vector2f v;

    v.x = x - rhs.x;
    v.y = y - rhs.y;

    return v;
};

Vector2f Vector2f::operator *(const Vector2f & rhs)
{
    Vector2f v;

    v.x = x * rhs.x;
    v.y = y * rhs.y;

    return v;
};

Vector2f Vector2f::operator /(const Vector2f & rhs)
{
    Vector2f v;

    v.x = x / rhs.x;
    v.y = y / rhs.y;

    return v;
};

Bool32 Vector2f::operator ==(const Vector2f & rhs)
{
    return (x == rhs.x && y == rhs.y);
};

Vector2f Vector2f::operator +(const Real32 & scalar)
{
    return Vector2f(x + scalar, y + scalar);
}

Vector2f Vector2f::operator -(const Real32 & scalar)
{
    return Vector2f(x - scalar, y - scalar);
}

Vector2f Vector2f::operator *(const Real32 & scalar)
{
    return Vector2f(x * scalar, y * scalar);
}

Vector2f Vector2f::operator /(const Real32 & scalar)
{
    return Vector2f(x / scalar, y / scalar);
}

template<>
inline Real32 LengthSquared (Vector2f & v)
{
    return v.x * v.x + v.y * v.y;
}

template<>
inline Real32 Length (Vector2f & v)
{
    return SquareRoot(LengthSquared(v));
}

template<>
inline Vector2f Normalize (Vector2f & v)
{
    return v / Length(v);
}

template<>
inline Vector2f Cross (Vector2f & v1, Vector2f & v2)
{
    return Vector2f();
}

template<>
inline Real32 Dot (Vector2f & v1, Vector2f & v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

template<>
inline Real32 Angle (Vector2f & v1, Vector2f & v2)
{
    return Cos(Dot(v1, v2) / Length(v1) * Length(v2));
}

template <>
inline Vector2f Lerp (Vector2f & start, Vector2f & end, Real32 t)
{
    return start * (1.0f - t) + end * t;
}
//==== Implementation end ====//

#endif
