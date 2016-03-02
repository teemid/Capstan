#ifndef CAPSTAN_MATH_MATRIX4_H
#define CAPSTAN_MATH_MATRIX4_H

#include "Platform/Memory.h"

#include "Math/Matrix.h"


namespace Capstan
{
    template<>
    struct Matrix<Real32, 4>
    {
        union {
            Real32 data[16];
            Vector4f rows[4];
        };

        Matrix (void);
        Matrix (Vector4f & v);
        Matrix (Vector4f c1, Vector4f c2, Vector4f c3, Vector4f c4);

        Matrix4f operator +(const Matrix4f & rhs);
        Matrix4f operator -(const Matrix4f & rhs);
        Matrix4f operator *(const Matrix4f & rhs);

        Vector4f & operator [](UInt32 row);

        Matrix4f operator ==(const Matrix4f & rhs);
    };

    Matrix4f Identity (void);

    Matrix4f Rotate (Vector3f & radians);
    Matrix4f RotateX (Real32 radians);
    Matrix4f RotateY (Real32 radians);
    Matrix4f RotateZ (Real32 radians);

    Matrix4f Translate (Vector3f & translation);
    Matrix4f TranslateX (Real32 x);
    Matrix4f TranslateY (Real32 x);
    Matrix4f TranslateZ (Real32 x);

    Matrix4f Scale (Vector3f & scaling);
    Matrix4f ScaleX (Real32 scaling);
    Matrix4f ScaleY (Real32 scaling);
    Matrix4f ScaleZ (Real32 scaling);

    Matrix4f Share ();

    Matrix<Real32, 4>::Matrix (void)
    {
        Memory::Zero((void *)data, sizeof(Real32) * 16);
    };

    Matrix<Real32, 4>::Matrix (Vector4f & v)
    {
        rows[0] = v;
        rows[1] = v;
        rows[2] = v;
        rows[3] = v;
    };

    Vector4f & Matrix<Real32, 4>::operator [](UInt32 row)
    {
        return rows[row];
    }

    Matrix4f Matrix<Real32, 4>::operator +(const Matrix4f & rhs)
    {
        Matrix4f result = {};
        Int32 i;

        for (Int32 row = 0; row < 4; ++row)
        {
            for (Int32 column = 0; column < 4; ++column)
            {
                i = column * 4 + row;

                result.data[i] = data[i] + rhs.data[i];
            }
        }

        return result;
    }

    Matrix4f Matrix<Real32, 4>::operator -(const Matrix4f & rhs)
    {
        Matrix4f result = {};
        Int32 i;

        for (Int32 row = 0; row < 4; ++row)
        {
            for (Int32 column = 0; column < 4; ++column)
            {
                i = column * 4 + row;

                result.data[i] = data[i] - rhs.data[i];
            }
        }

        return result;
    }

    Matrix4f Matrix<Real32, 4>::operator *(const Matrix4f & rhs)
    {
        Matrix4f result = {};

        for (Int32 row = 0; row < 4; ++row)
        {
            for (Int32 column = 0; column < 4; ++column)
            {
                result.data[column + row * 4] = (
                    data[column * 4 + 0] * rhs.data[column +  0] +
                    data[column * 4 + 1] * rhs.data[column +  4] +
                    data[column * 4 + 2] * rhs.data[column +  8] +
                    data[column * 4 + 3] * rhs.data[column + 12]
                );
            }
        }

        return result;
    }
}

#endif
