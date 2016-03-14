#ifndef CAPSTAN_MATH_MATRIX4F_H
#define CAPSTAN_MATH_MATRIX4F_H

#include "Platform/Intrinsics.h"
#include "Platform/Memory.h"
#include "Platform/Types.h"

#include "Math/Constants.h"
#include "Math/Vector3f.h"
#include "Math/Vector4f.h"


namespace Capstan
{
    struct Matrix4f
    {
        union {
            Real32 data[16];
            Vector4f rows[4];
        };

        Matrix4f (void);
        Matrix4f (Vector4f & v);
        Matrix4f (Vector4f c1, Vector4f c2, Vector4f c3, Vector4f c4);

        Matrix4f operator +(const Matrix4f & rhs);
        Matrix4f operator -(const Matrix4f & rhs);
        Matrix4f operator *(const Matrix4f & rhs);

        Vector4f operator *(const Vector4f & columnVector);

        Vector4f operator [](UInt32 row) const;
        Vector4f & operator [](UInt32 row);

        Matrix4f & operator =(const Matrix4f & rhs);
        Bool32 operator ==(const Matrix4f & rhs);
    };

    Matrix4f Identity (void);

    Matrix4f Transpose (Matrix4f * matrix);

    Matrix4f Rotate (Matrix4f & m, Real32 angle, Vector3f axis);
    Matrix4f Rotate (Real32 angle, Vector3f axis);
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

    namespace Projection
    {
        Matrix4f Orthographic (Real32 left, Real32 right, Real32 bottom, Real32 top, Real32 zNear, Real32 zFar);
        Matrix4f Perspective (Real32 fov, Real32 aspect, Real32 zNear, Real32 zFar);
    }

    Matrix4f::Matrix4f (void)
    {
        rows[0][0] = 1;
        rows[1][1] = 1;
        rows[2][2] = 1;
        rows[3][3] = 1;
    };

    Matrix4f::Matrix4f (Vector4f & v)
    {
        rows[0] = v;
        rows[1] = v;
        rows[2] = v;
        rows[3] = v;
    };

    Vector4f Matrix4f::operator [](UInt32 row) const
    {
        return rows[row];
    }

    Vector4f & Matrix4f::operator [](UInt32 row)
    {
        return rows[row];
    }

    Matrix4f Matrix4f::operator +(const Matrix4f & rhs)
    {
        Matrix4f result = {};

        for (Int32 row = 0; row < 4; ++row)
        {
            for (Int32 column = 0; column < 4; ++column)
            {
                result[row][column] = rows[row][column] + rhs[row][column];
            }
        }

        return result;
    }

    Matrix4f Matrix4f::operator -(const Matrix4f & rhs)
    {
        Matrix4f result = {};

        for (Int32 row = 0; row < 4; ++row)
        {
            for (Int32 column = 0; column < 4; ++column)
            {
                result[row][column] = rows[row][column] - rhs[row][column];
            }
        }

        return result;
    }

    // TODO (Emil): Optimize matrix multiplication, possibly with intrinsics.
    Matrix4f Matrix4f::operator *(const Matrix4f & rhs)
    {
        Matrix4f result = {};

        for (UInt32 i = 0; i < 4; ++i)
        {
            for (UInt32 j = 0; j < 4; ++j)
            {
                for (UInt32 k = 0; k < 4; ++k)
                {
                    result[i][j] += rows[i][k] * rhs[k][j];
                }
            }
        }

        return result;
    }

    Vector4f Matrix4f::operator *(const Vector4f & columnVector)
    {
        Vector4f result;

        for (UInt32 i = 0; i < 4; ++i)
        {
            Real32 x = rows[i][0] * columnVector.x;
            Real32 y = rows[i][1] * columnVector.y;
            Real32 z = rows[i][2] * columnVector.z;
            Real32 w = rows[i][3] * columnVector.w;

            result[i] = x + y + z + w;
        }

        return result;
    }

    Matrix4f & Matrix4f::operator =(const Matrix4f & m)
    {
        rows[0] = m[0];
        rows[1] = m[1];
        rows[2] = m[2];
        rows[3] = m[3];

        return *this;
    }

    Bool32 Matrix4f::operator ==(const Matrix4f & rhs)
    {
        for (UInt32 row = 0; row < 4; ++row)
        {
            for (UInt32 column = 0; column < 4; ++column)
            {
                if (rows[row][column] != rhs[row][column])
                {
                    return false;
                }
            }
        }

        return true;
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


    Matrix4f Rotate (Real32 theta, Vector3f axis)
    {
        Matrix4f result;

        Real32 c = Cos(theta);
        Real32 c_inv = 1 - c;
        Real32 s = Sin(theta);

        result[0][0] = c + axis.x * axis.x * c_inv;
        result[0][1] = axis.x * axis.y * c_inv - axis.z * s;
        result[0][2] = axis.x * axis.z * c_inv + axis.y * s;
        result[0][3] = 0;

        result[1][0] = axis.x * axis.y * c_inv + axis.z * s;
        result[1][1] = c + axis.y * axis.y * c_inv;
        result[1][2] = axis.y * axis.z * c_inv - axis.x * s;
        result[1][3] = 0;

        result[2][0] = axis.z * axis.x * c_inv - axis.y * s;
        result[2][1] = axis.z * axis.y * c_inv + axis.x * s;
        result[2][2] = c + axis.z * axis.z * c_inv;
        result[2][3] = 0;

        result[3] = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);

        return result;
    }


    // NOTE (Emil): Rotates theta degrees around the axis defined by the
    // unit vector axis.
    Matrix4f Rotate(Matrix4f & m, Real32 theta, Vector3f axis)
    {
        Matrix4f result = Rotate(theta, axis);

        return m * result;
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

    namespace Projection
    {
        Matrix4f Orthographic (
            Real32 left,
            Real32 right,
            Real32 bottom,
            Real32 top,
            Real32 zNear,
            Real32 zFar
        )
        {
            Matrix4f ortho;

            ortho[0][0] =  2.0f / (right - left);
            ortho[1][1] =  2.0f / (top - bottom);
            ortho[2][2] = -2.0f / (zFar - zNear);

            ortho[0][3] = -(right + left) / (right - left);
            ortho[1][3] = -(top + bottom) / (top - bottom);
            ortho[2][3] = -(zFar + zNear) / (zFar - zNear);

            ortho[3] = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);

            return ortho;
        }

        Matrix4f Perspective (Real32 fov, Real32 aspect, Real32 zNear, Real32 zFar)
        {
            Matrix4f perspective;

            Real32 s = 1 / (Tan((fov / 2) * (PI / 180)));

            perspective[0][0] = s;

            perspective[1][1] = s;

            perspective[2][2] = -zFar / (zFar - zNear);
            perspective[2][3] = -1;

            perspective[3][2] = -(zFar * zNear) / (zFar - zNear);

            return perspective;
        }
    }
}

#endif
