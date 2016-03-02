#ifndef CAPSTAN_MATRIX_H
#define CAPSTAN_MATRIX_H

#include "Math/Vector.h"

#include "Platform/Memory.h"
#include "Platform/Types.h"


namespace Capstan
{
    // TODO (Emil): Assuming that I only need NxN matricies, at least in the near future.
    template<typename T, UInt32 N>
    struct Matrix
    {
        union
        {
            T data[N * N];
            Vector<T, N> rows[N];
        };

        Matrix (void);

        Vector<T, N> & operator [](UInt32 row);

        Matrix<T, N> operator +(const Matrix<T, N> & rhs);
        Matrix<T, N> operator -(const Matrix<T, N> & rhs);
        Matrix<T, N> operator *(const Matrix<T, N> & rhs);
    };

    typedef Matrix<Real32, 4> Matrix4f;

    template<typename T, UInt32 N>
    Matrix<T, N> Translate (Vector<T, N> & v);

    template<typename T, UInt32 N>
    Matrix<T, N> Rotate (Vector<T, N> & v);

    template<typename T, UInt32 N>
    Matrix<T, N>::Matrix (void)
    {
        Memory::Zero(data, sizof(T) * N);
    }

    template<typename T, UInt32 N>
    Vector<T, N> & Matrix<T, N>::operator [](UInt32 row)
    {
        return rows[row];
    }

    template<typename T, UInt32 N>
    Matrix<T, N> Matrix<T, N>::operator +(const Matrix<T, N> & rhs)
    {
        Matrix<T, N> result;

        for (UInt32 row = 0; row < N; ++row)
        {
            for (UInt32 column = 0; column < N; ++column)
            {
                result[row][column] = this[row][column] + rhs[row][column];
            }
        }

        return result;
    }
}


#endif
