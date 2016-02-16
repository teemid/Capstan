#ifndef CAPSTAN_VECTOR_H
#define CAPSTAN_VECTOR_H


#include "types.h"


namespace Capstan
{
    template <typename T, UInt32 N>
    struct Vector
    {
        T data[N];

        Vector (void);
        Vector (T x);

        Vector<T, N> operator +(const Vector<T, N> & rhs);
        Vector<T, N> operator -(const Vector<T, N> & rhs);
        Vector<T, N> operator *(const Vector<T, N> & rhs);
        Vector<T, N> operator /(const Vector<T, N> & rhs);

        Vector<T, N> operator +(const T scalar);
        Vector<T, N> operator -(const T scalar);
        Vector<T, N> operator *(const T scalar);
        Vector<T, N> operator /(const T scalar);

        Bool32 operator ==(const Vector<T, N> & rhs);
    };

    template<typename T, UInt32 N>
    Vector<T, N> Normalize (Vector<T, N> & v);

    template<typename T, UInt32 N>
    T LengthSquared (Vector<T, N> & v);

    template<typename T, UInt32 N>
    T Length (Vector<T, N> & v);

    template<typename T, UInt32 N>
    T Dot (Vector<T, N> & v1, Vector<T, N> & v2);

    template<typename T, UInt32 N>
    Real32 Angle (Vector<T, N> & v1, Vector<T, N> & v2);

    template <typename T, UInt32 N>
    Vector<T, N> Lerp (Vector<T, N> & start, Vector<T, N> & end, Real32 t);

    typedef Vector<Real32, 2> Vector2f;
    typedef Vector<Real32, 3> Vector3f;
    typedef Vector<Real32, 4> Vector4f;

    typedef Vector<Int32, 2> Vector2i;
    typedef Vector<Int32, 3> Vector3i;
    typedef Vector<Int32, 4> Vector4i;

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

    template<> struct Vector<Real32, 3>
    {
        union {
            Real32 data[3];
            struct { Real32 x, y, z; };
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
        Bool32 operator ==(const Vector3f & rhs);
    };

    template<> struct Vector<Real32, 4> {
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
        Vector4f operator /(const Vector4f & rhs);
        Bool32 operator ==(const Vector4f & rhs);
    };
}

#include "Vector/Vector.inl"
#include "Vector/Vector2f.inl"
#include "Vector/Vector3f.inl"

#endif
