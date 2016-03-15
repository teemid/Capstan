#include "Math/Matrix4f.h"


namespace Capstan
{
    Matrix4f::Matrix4f (void)
    {
        rows[0] = Vector4f(1.0f, 0.0f, 0.0f, 0.0f);
        rows[1] = Vector4f(0.0f, 1.0f, 0.0f, 0.0f);
        rows[2] = Vector4f(0.0f, 0.0f, 1.0f, 0.0f);
        rows[3] = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4f::Matrix4f (Vector4f & v)
    {
        rows[0] = v;
        rows[1] = v;
        rows[2] = v;
        rows[3] = v;
    }

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
}
