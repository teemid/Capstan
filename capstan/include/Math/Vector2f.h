#ifndef CAPSTAN_MATH_VECTOR2_H
#define CAPSTAN_MATH_VECTOR2_H


template<>
struct Vector<Real32, 2>
{
    union {
        Real32 data[2];
        struct { Real32 x, y; };
    };

    Vector (void);
    Vector (Real32 x);
    Vector (Real32 x, Real32 y);

    Vector2f operator +(const Vector2f & rhs);
    Vector2f operator -(const Vector2f & rhs);
    Vector2f operator *(const Vector2f & rhs);
    Vector2f operator /(const Vector2f & rhs);

    Vector2f operator +(const Real32 scalar);
    Vector2f operator -(const Real32 scalar);
    Vector2f operator *(const Real32 scalar);
    Vector2f operator /(const Real32 scalar);

    Bool32 operator ==(const Vector2f & rhs);
};

template<>
Real32 LengthSquared<Real32, 2> (Vector2f & v);

template<>
Real32 Length<Real32, 2> (Vector2f & v);

template<>
Real32 Dot (Vector2f & v1, Vector2f & v2);

Vector2f Cross (Vector2f & v1, Vector2f & v2);

template<>
Vector2f Lerp (Vector2f & start, Vector2f & end, Real32 t);

//==== Implementation begin ====//
Vector<Real32, 2>::Vector (void) : x(0), y(0) { };

Vector<Real32, 2>::Vector (Real32 x) : x(x), y(x) { };

Vector<Real32, 2>::Vector (Real32 x, Real32 y) : x(x), y(y) { };

Vector2f Vector<Real32, 2>::operator +(const Vector2f & rhs)
{
    Vector2f v;

    v.x = x + rhs.x;
    v.y = y + rhs.y;

    return v;
};

Vector2f Vector<Real32, 2>::operator -(const Vector2f & rhs)
{
    Vector2f v;

    v.x = x - rhs.x;
    v.y = y - rhs.y;

    return v;
};

Vector2f Vector<Real32, 2>::operator *(const Vector2f & rhs)
{
    Vector2f v;

    v.x = x * rhs.x;
    v.y = y * rhs.y;

    return v;
};

Vector2f Vector<Real32, 2>::operator /(const Vector2f & rhs)
{
    Vector2f v;

    v.x = x / rhs.x;
    v.y = y / rhs.y;

    return v;
};

Bool32 Vector<Real32, 2>::operator ==(const Vector2f & rhs)
{
    return (x == rhs.x && y == rhs.y);
};

template<>
Real32 LengthSquared<Real32, 2> (Vector2f & v)
{
    return v.x * v.x + v.y * v.y;
};

template<>
Real32 Length<Real32, 2> (Vector2f & v)
{
    return (v.x * v.x + v.y * v.y) / 2;
}
//==== Implementation end ====//

#endif
