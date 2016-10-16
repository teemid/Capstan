#ifndef CAPSTAN_MATH_MATRIX4F_H
#define CAPSTAN_MATH_MATRIX4F_H

#include "Capstan/Platform/Intrinsics.h"
#include "Capstan/Platform/Memory.h"
#include "Capstan/Types.h"

#include "Capstan/Math/Constants.h"
#include "Capstan/Math/Vector3f.h"
#include "Capstan/Math/Vector4f.h"


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

    inline Matrix4f Identity (void);

    inline Matrix4f Transpose (Matrix4f * matrix);

    inline Matrix4f Rotate (Matrix4f & m, Real32 angle, Vector3f axis);
    inline Matrix4f Rotate (Real32 angle, Vector3f axis);
    inline Matrix4f RotateX (Real32 radians);
    inline Matrix4f RotateY (Real32 radians);
    inline Matrix4f RotateZ (Real32 radians);

    inline Matrix4f Translate (Vector3f & translation);
    inline Matrix4f TranslateX (Real32 x);
    inline Matrix4f TranslateY (Real32 x);
    inline Matrix4f TranslateZ (Real32 x);

    inline Matrix4f Scale (Vector3f & scaling);
    inline Matrix4f ScaleX (Real32 scaling);
    inline Matrix4f ScaleY (Real32 scaling);
    inline Matrix4f ScaleZ (Real32 scaling);

    namespace Projection
    {
        inline Matrix4f Orthographic (Real32 left, Real32 right, Real32 bottom, Real32 top, Real32 zNear, Real32 zFar);
        inline Matrix4f Perspective (Real32 fov, Real32 aspect, Real32 zNear, Real32 zFar);
    }

    inline Matrix4f Identity (void)
    {
        Matrix4f identity;

        identity[0].x = 1;
        identity[1].y = 1;
        identity[2].z = 1;
        identity[3].w = 1;

        return identity;
    }

    inline Matrix4f Transpose (Matrix4f * matrix)
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

    inline Matrix4f Rotate (Real32 theta, Vector3f axis)
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
    inline Matrix4f Rotate(Matrix4f & m, Real32 theta, Vector3f axis)
    {
        Matrix4f result = Rotate(theta, axis);

        return m * result;
    }

    inline Matrix4f RotateX (Real32 radians)
    {
        Matrix4f transform = Identity();

        transform[1].y =  Cos(radians);
        transform[1].z = -Sin(radians);
        transform[2].y =  Sin(radians);
        transform[2].z =  Cos(radians);

        return transform;
    }

    inline Matrix4f RotateY (Real32 radians)
    {
        Matrix4f transform = Identity();

        transform[0].x =  Cos(radians);
        transform[0].z =  Sin(radians);
        transform[2].x = -Sin(radians);
        transform[2].z =  Cos(radians);

        return transform;
    }

    inline Matrix4f RotateZ (Real32 radians)
    {
        Matrix4f transform = Identity();

        transform[0].x =  Cos(radians);
        transform[0].y = -Sin(radians);
        transform[1].x =  Sin(radians);
        transform[1].y =  Cos(radians);

        return transform;
    }

    inline Matrix4f Translate (Vector3f & translation)
    {
        Matrix4f transform = Identity();

        transform[0].w = translation.x;
        transform[1].w = translation.y;
        transform[2].w = translation.z;

        return transform;
    }

    inline Matrix4f TranslateX (Real32 x)
    {
        Matrix4f transform = Identity();

        transform[0].w = x;

        return transform;
    }

    inline Matrix4f TranslateY (Real32 y)
    {
        Matrix4f transform = Identity();

        transform[1].w = y;

        return transform;
    }

    inline Matrix4f TranslateZ (Real32 z)
    {
        Matrix4f transform = Identity();

        transform[2].w = z;

        return transform;
    }

    inline Matrix4f Scale (Vector3f & scaling)
    {
        Matrix4f transform = Identity();

        transform[0].x = scaling.x;
        transform[1].y = scaling.y;
        transform[2].z = scaling.z;

        return transform;
    }

    inline Matrix4f ScaleX (Real32 scaling)
    {
        Matrix4f transform = Identity();

        transform[0].x = scaling;

        return transform;
    }

    inline Matrix4f ScaleY (Real32 scaling)
    {
        Matrix4f transform = Identity();

        transform[1].y = scaling;

        return transform;
    }

    inline Matrix4f ScaleZ (Real32 scaling)
    {
        Matrix4f transform = Identity();

        transform[2].z = scaling;

        return transform;
    }

    namespace Projection
    {
        inline Matrix4f Orthographic (
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

        inline Matrix4f Perspective (Real32 fov, Real32 aspect, Real32 zNear, Real32 zFar)
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
