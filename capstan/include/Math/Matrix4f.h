#ifndef CAPSTAN_MATH_MATRIX4_H
#define CAPSTAN_MATH_MATRIX4_H

#include "Platform/Memory.h"
#include "Platform/Intrinsics.h"

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

        Vector4f operator *(const Vector4f & columnVector);

        Vector4f & operator [](UInt32 row);

        Matrix4f operator ==(const Matrix4f & rhs);
    };

    Matrix4f Identity (void);

    Matrix4f Transpose (Matrix4f * matrix);

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

    // TODO (Emil): Optimize matrix multiplication, possibly with intrinsics.
    Matrix4f Matrix<Real32, 4>::operator *(const Matrix4f & rhs)
    {
        Matrix4f result = {};

        for (UInt32 i = 0; i < 4; ++i)
        {
            for (UInt32 j = 0; j < 4; ++j)
            {
                for (UInt32 k = 0; k < 4; ++k)
                {
                    result[i][j] += rows[i][k] * rhs.data[k * 4 + j];
                }
            }
        }

        return result;
    }

    Vector4f Matrix<Real32, 4>::operator *(const Vector4f & columnVector)
    {
        Vector4f result;

        for (UInt32 i = 0; i < 4; ++i)
        {
            Real32 x = data[i * 4 + 0] * columnVector.x;
            Real32 y = data[i * 4 + 1] * columnVector.y;
            Real32 z = data[i * 4 + 2] * columnVector.z;
            Real32 w = data[i * 4 + 3] * columnVector.w;

            result[i] = x + y + z + w;
        }

        return result;
    }

    Matrix4f Identity (void)
    {
        Matrix4f identity;

        identity[0].x = 1;
        identity[1].y = 1;
        identity[2].z = 1;
        identity[3].w = 1;

        return identity;
    }


    Matrix4f Transpose (Matrix4f * matrix)
    {
        Matrix4f result;

        for (UInt32 r = 0; r < 4; ++r)
        {
            for (UInt32 c = 0; c < 4; ++c)
            {
                result[c][r] = (*matrix)[r][c];
            }
        }

        return result;
    }

    Matrix4f Rotate (Vector3f & radians)
    {
        Matrix4f transform;

        return transform;
    }

    Matrix4f RotateX (Real32 radians)
    {
        Matrix4f transform = Identity();

        transform[1].y =  Cos(radians);
        transform[1].z = -Sin(radians);
        transform[2].y =  Sin(radians);
        transform[2].z =  Cos(radians);

        return transform;
    }

    Matrix4f RotateY (Real32 radians)
    {
        Matrix4f transform = Identity();

        transform[0].x =  Cos(radians);
        transform[0].z =  Sin(radians);
        transform[2].x = -Sin(radians);
        transform[2].z =  Cos(radians);

        return transform;
    }

    Matrix4f RotateZ (Real32 radians)
    {
        Matrix4f transform = Identity();

        transform[0].x =  Cos(radians);
        transform[0].y = -Sin(radians);
        transform[1].x =  Sin(radians);
        transform[1].y =  Cos(radians);

        return transform;
    }

    Matrix4f Translate (Vector3f & translation)
    {
        Matrix4f transform = Identity();

        transform[0].w = translation.x;
        transform[1].w = translation.y;
        transform[2].w = translation.z;

        return transform;
    }

    Matrix4f TranslateX (Real32 x)
    {
        Matrix4f transform = Identity();

        transform[0].w = x;

        return transform;
    }

    Matrix4f TranslateY (Real32 y)
    {
        Matrix4f transform = Identity();

        transform[1].w = y;

        return transform;
    }

    Matrix4f TranslateZ (Real32 z)
    {
        Matrix4f transform = Identity();

        transform[2].w = z;

        return transform;
    }

    Matrix4f Scale (Vector3f & scaling)
    {
        Matrix4f transform = Identity();

        transform[0].x = scaling.x;
        transform[1].y = scaling.y;
        transform[2].z = scaling.z;

        return transform;
    }

    Matrix4f ScaleX (Real32 scaling)
    {
        Matrix4f transform = Identity();

        transform[0].x = scaling;

        return transform;
    }

    Matrix4f ScaleY (Real32 scaling)
    {
        Matrix4f transform = Identity();

        transform[1].y = scaling;

        return transform;
    }
    Matrix4f ScaleZ (Real32 scaling)
    {
        Matrix4f transform = Identity();

        transform[2].z = scaling;

        return transform;
    }
}

#endif
