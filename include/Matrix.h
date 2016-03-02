#ifndef CAPSTAN_MATRIX_H
#define CAPSTAN_MATRIX_H


#include "Vector.h"
#include "types.h"


namespace Capstan
{
    // TODO (Emil): Assuming that I only need NxN matricies, at least in the near future.
    template<typename T, UInt32 N>
    struct Matrix
    {
        T data[N * N];

        Matrix (void);

        Matrix<T, N> operator +(const Matrix<T, N> & rhs);
        Matrix<T, N> operator +(const Matrix<T, N> & rhs);
        Matrix<T, N> operator *(const Matrix<T, N> & rhs);
    };

    template<typename T, UInt32 N>
    Matrix<T, N> Translate (Vector<T, N> & v);

    template<typename T, UInt32 N>
    Matrix<T, N> Rotate (Vector<T, N> & v);

    typedef Matrix<Real32, 4> Matrix4f;
    typedef Matrix<Real32, 3> Matrix3f;
    typedef Matrix<Real32, 4> Matrix2f;

    template<>
    struct Matrix<Real32, 4>
    {
        union {
            Real32 data[16];
            struct {
                Vector<Real32, 4> column1;
                Vector<Real32, 4> column2;
                Vector<Real32, 4> column3;
                Vector<Real32, 4> column4;
            };
            struct {
                Real32 a11;
                Real32 a21;
                Real32 a31;
                Real32 a41;
                Real32 a12;
                Real32 a22;
                Real32 a32;
                Real32 a42;
                Real32 a13;
                Real32 a23;
                Real32 a33;
                Real32 a43;
                Real32 a14;
                Real32 a24;
                Real32 a34;
                Real32 a44;
            };
        };

        Matrix (void);
        Matrix (Vector v);
        Matrix (Vector c1, Vector c2, Vector c3, Vector c4);

        Matrix4f operator +(const Matrix4f & rhs);
        Matrix4f operator -(const Matrix4f & rhs);
        Matrix4f operator *(const Matrix4f & rhs);

        Matrix4f operator ==(const Matrix4f & rhs);
    };
}


#endif
