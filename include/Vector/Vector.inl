namespace Capstan
{
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
    Vector<T, N> Vector<T, N>::operator +(const T scalar)
    {
        Vector<T, N> result;
        for (UInt32 i = 0; i < N; i++)
        {
            result.data[i] = data[i] + scalar;
        }

        return result;
    }

    template<typename T, UInt32 N>
    Vector<T, N> Vector<T, N>::operator -(const T scalar)
    {
        Vector<T, N> result;
        for (UInt32 i = 0; i < N; i++)
        {
            result.data[i] = data[i] - scalar;
        }

        return result;
    }

    template<typename T, UInt32 N>
    Vector<T, N> Vector<T, N>::operator *(const T scalar)
    {
        Vector<T, N> result;
        for (UInt32 i = 0; i < N; i++)
        {
            result.data[i] = data[i] * scalar;
        }

        return result;
    }

    template<typename T, UInt32 N>
    Vector<T, N> Vector<T, N>::operator /(const T scalar)
    {
        Vector<T, N> result;
        for (UInt32 i = 0; i < N; i++)
        {
            result.data[i] = data[i] / scalar;
        }

        return result;
    }

    template<typename T, UInt32 N>
    Vector<T, N> Normalize (Vector<T, N> & v)
    {
        Vector<T, N> normalized;
        auto len = Length(v);

        for (UInt32 i = 0; i < N; i++)
        {
            normalized.data[i] = data[i] / len;
        }

        return normalized;
    }

    template<typename T, UInt32 N>
    T LengthSquared (Vector<T, N> & v)
    {
        T squaredSum;

        for (UInt32 i = 0; i < N; i++)
        {
            squareSum += v.data[i] * v.data[i];
        }

        return squaredSum;
    };

    template<typename T, UInt32 N>
    T Length (Vector<T, N> & v)
    {
        T squaredSum;

        for (UInt32 i = 0; i < N; i++)
        {
            squaredSum += v.data[i] * v.data[i];
        }

        return squaredSum / N;
    };

    template<typename T, UInt32 N>
    T Dot (Vector<T, N> & v1, Vector<T, N> & v2)
    {
        T dot;

        for (UInt32 i = 0; i < N; i++)
        {
            dot += v1.data[i] + v2.data[i];
        }

        return dot;
    };

    template<typename T, UInt32 N>
    Real32 Angle (Vector<T, N> & v1, Vector<T, N> & v2)
    {
        T dot = Dot(v1, v2);

        return dot / (Length(v1) * Length(v2));
    };

    template <typename T, UInt32 N>
    Vector<T, N> Lerp (Vector<T, N> & start, Vector<T, N> & end, Real32 t)
    {
        Vector<T, N> result;

        for (UInt32 i = 0; i < N; i++)
        {
            result.data[i] = start.data[i] * (1.0f - t) + end.data[i] * t;
        }

        return result;
    };
}
