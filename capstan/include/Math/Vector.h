#ifndef CAPSTAN_MATH_VECTOR_H
#define CAPSTAN_MATH_VECTOR_H


#include "Platform/Types.h"


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

        Vector<T, N> operator +(const T & scalar);
        Vector<T, N> operator -(const T & scalar);
        Vector<T, N> operator *(const T & scalar);
        Vector<T, N> operator /(const T & scalar);

        T operator[](UInt32 index);

        Bool32 operator ==(const Vector<T, N> & rhs);
    };

    typedef Vector<Real32, 2> Vector2f;
    typedef Vector<Real32, 3> Vector3f;
    typedef Vector<Real32, 4> Vector4f;

    typedef Vector2f UVMap;
    typedef Vector3f Color3f;
    typedef Vector4f Color4f;

    typedef Vector<Int32, 2> Vector2i;
    typedef Vector<Int32, 3> Vector3i;
    typedef Vector<Int32, 4> Vector4i;

    template<typename T, UInt32 N>
    Vector<T, N> Normalize (Vector<T, N> & v);

    template<typename T, UInt32 N>
    T LengthSquared (Vector<T, N> & v);

    template<typename T, UInt32 N>
    T Length (Vector<T, N> & v);

    template<typename T, UInt32 N>
    Vector<T, N> Cross (Vector<T, N> & v1, Vector<T, N> & v2);

    template<typename T, UInt32 N>
    T Dot (Vector<T, N> & v1, Vector<T, N> & v2);

    template<typename T, UInt32 N>
    Real32 Angle (Vector<T, N> & v1, Vector<T, N> & v2);

    template <typename T, UInt32 N>
    Vector<T, N> Lerp (Vector<T, N> & start, Vector<T, N> & end, Real32 t);

    template<typename T, UInt32 N>
    Vector<T, N>::Vector (void)
    {
        for (UInt32 i = 0; i < N; i++)
        {
            data[i] = 0;
        }
    };

    template<typename T, UInt32 N>
    Vector<T, N>::Vector (T x)
    {
        for (UInt32 i = 0; i < N; i++)
        {
            data[i] = x;
        }
    };

    template<typename T, UInt32 N>
    T Vector<T, N>::operator[](UInt32 index)
    {
        return data[index];
    }

    template<typename T, UInt32 N>
    Vector<T, N> Vector<T, N>::operator +(const Vector<T, N> & rhs)
    {
        Vector<T, N> res;

        for (UInt32 i = 0; i < N; i++)
        {
            res = data[i] + rhs.data[i];
        }

        return res;
    };

    template<typename T, UInt32 N>
    Vector<T, N> Vector<T, N>::operator -(const Vector<T, N> & rhs)
    {
        Vector<T, N> res;

        for (UInt32 i = 0; i < N; i++)
        {
            res = data[i] - rhs.data[i];
        }

        return res;
    };

    template<typename T, UInt32 N>
    Vector<T, N> Vector<T, N>::operator *(const Vector<T, N> & rhs)
    {
        Vector<T, N> res;

        for (UInt32 i = 0; i < N; i++)
        {
            res = data[i] * rhs.data[i];
        }

        return res;
    };

    template<typename T, UInt32 N>
    Vector<T, N> Vector<T, N>::operator /(const Vector<T, N> & rhs)
    {
        Vector<T, N> res;

        for (UInt32 i = 0; i < N; i++)
        {
            res = data[i] / rhs.data[i];
        }

        return res;
    };

    template<typename T, UInt32 N>
    Bool32 Vector<T, N>::operator ==(const Vector<T, N> & rhs)
    {
        for (UInt32 i = 0; i < N; i++)
        {
            if (data[i] != rhs.data[i])
            {
                return false;
            }
        }

        return true;
    };

    template<typename T, UInt32 N>
    Vector<T, N> Vector<T, N>::operator +(const T & scalar)
    {
        Vector<T, N> result;
        for (UInt32 i = 0; i < N; i++)
        {
            result.data[i] = data[i] + scalar;
        }

        return result;
    }

    template<typename T, UInt32 N>
    Vector<T, N> Vector<T, N>::operator -(const T & scalar)
    {
        Vector<T, N> result;
        for (UInt32 i = 0; i < N; i++)
        {
            result.data[i] = data[i] - scalar;
        }

        return result;
    }

    template<typename T, UInt32 N>
    Vector<T, N> Vector<T, N>::operator *(const T & scalar)
    {
        Vector<T, N> result;
        for (UInt32 i = 0; i < N; i++)
        {
            result.data[i] = data[i] * scalar;
        }

        return result;
    }

    template<typename T, UInt32 N>
    Vector<T, N> Vector<T, N>::operator /(const T & scalar)
    {
        Vector<T, N> result;
        for (UInt32 i = 0; i < N; i++)
        {
            result.data[i] = data[i] / scalar;
        }

        return result;
    }

    template<typename T, UInt32 N>
    inline T LengthSquared (Vector<T, N> & v)
    {
        T squaredSum;

        for (UInt32 i = 0; i < N; i++)
        {
            squareSum += v.data[i] * v.data[i];
        }

        return squaredSum;
    };

    template<typename T, UInt32 N>
    inline T Length (Vector<T, N> & v)
    {
        T squaredSum;

        for (UInt32 i = 0; i < N; i++)
        {
            squaredSum += v.data[i] * v.data[i];
        }

        return squaredSum / N;
    };

    template<typename T, UInt32 N>
    inline Vector<T, N> Normalize (Vector<T, N> & v)
    {
        return v / Length(v);
    }



    template<typename T, UInt32 N>
    inline T Dot (Vector<T, N> & v1, Vector<T, N> & v2)
    {
        T dot;

        for (UInt32 i = 0; i < N; i++)
        {
            dot += v1.data[i] + v2.data[i];
        }

        return dot;
    };

    template<typename T, UInt32 N>
    inline Real32 Angle (Vector<T, N> & v1, Vector<T, N> & v2)
    {
        T dot = Dot(v1, v2);

        return dot / (Length(v1) * Length(v2));
    };

    template <typename T, UInt32 N>
    inline Vector<T, N> Lerp (Vector<T, N> & start, Vector<T, N> & end, Real32 t)
    {
        Vector<T, N> result;

        for (UInt32 i = 0; i < N; i++)
        {
            result.data[i] = start.data[i] * (1.0f - t) + end.data[i] * t;
        }

        return result;
    };

    #include "Math/Vector2f.h"
    #include "Math/Vector3f.h"
    #include "Math/Vector4f.h"
}


#endif
