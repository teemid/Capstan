namespace Capstan
{
    Vector<Real32, 3>::Vector (void)
    {
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;
    };

    Vector<Real32, 3>::Vector (Real32 x)
    {
        data[0] = x;
        data[1] = x;
        data[2] = x;
    };

    Vector<Real32, 3>::Vector (Real32 x, Real32 y, Real32 z)
    {
        data[0] = x;
        data[1] = y;
        data[2] = z;
    };

    Vector3f Vector<Real32, 3>::operator +(const Vector3f & rhs)
    {
        Vector3f v;

        v.x = x + rhs.x;
        v.y = y + rhs.y;
        v.z = y + rhs.z;

        return v;
    };

    Vector<Real32, 3>::Vector (Vector2f & v)
    {
        Vector3f result;
        result.x = v.x;
        result.y = v.y;
        result.z = 0.0f;
    }

    Vector<Real32, 3>::Vector (Vector2f & v, Real32 f)
    {
        Vector3f result;
        result.x = v.x;
        result.y = v.y;
        result.z = f;
    }

    Vector3f Vector<Real32, 3>::operator -(const Vector3f & rhs)
    {
        Vector3f v;

        v.x = x - rhs.x;
        v.y = y - rhs.y;
        v.z = z - rhs.z;

        return v;
    };

    Vector3f Vector<Real32, 3>::operator *(const Vector3f & rhs)
    {
        Vector3f v;

        v.x = x * rhs.x;
        v.y = y * rhs.y;
        v.z = z * rhs.z;

        return v;
    };

    Vector3f Vector<Real32, 3>::operator /(const Vector3f & rhs)
    {
        Vector3f v;

        v.x = x / rhs.x;
        v.y = y / rhs.y;
        v.z = z / rhs.z;

        return v;
    };

    Bool32 Vector<Real32, 3>::operator ==(const Vector3f & rhs)
    {
        return (x == rhs.x && y == rhs.y && z == rhs.z);
    };

    template<>
    Real32 LengthSquared<Real32, 3> (Vector3f & v)
    {
        return v.x * v.x + v.y * v.y + v.z * v.z;
    };

    template<>
    Real32 Length<Real32, 3> (Vector3f & v)
    {
        return (v.x * v.x + v.y * v.y) / 2;
    }
}
