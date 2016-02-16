namespace Capstan
{
    Vector<Real32, 2>::Vector (void)
    {
        data[0] = 0;
        data[1] = 0;
    };

    Vector<Real32, 2>::Vector (Real32 x)
    {
        data[0] = x;
        data[1] = x;
    };

    Vector<Real32, 2>::Vector (Real32 x, Real32 y)
    {
        data[0] = x;
        data[1] = y;
    };

    Vector2f Vector<Real32, 2>::operator +(const Vector2f & rhs)
    {
        Vector2f v;

        v.x = x + rhs.x;
        v.y = y + rhs.y;

        return v;
    };

    Vector2f Vector<Real32, 2>::operator -(const Vector2f & rhs)
    {
        Vector2f v;

        v.x = x - rhs.x;
        v.y = y - rhs.y;

        return v;
    };

    Vector2f Vector<Real32, 2>::operator *(const Vector2f & rhs)
    {
        Vector2f v;

        v.x = x * rhs.x;
        v.y = y * rhs.y;

        return v;
    };

    Vector2f Vector<Real32, 2>::operator /(const Vector2f & rhs)
    {
        Vector2f v;

        v.x = x / rhs.x;
        v.y = y / rhs.y;

        return v;
    };

    Bool32 Vector<Real32, 2>::operator ==(const Vector2f & rhs)
    {
        return (x == rhs.x && y == rhs.y);
    };

    template<>
    Real32 LengthSquared<Real32, 2> (Vector2f & v)
    {
        return v.x * v.x + v.y * v.y;
    };

    template<>
    Real32 Length<Real32, 2> (Vector2f & v)
    {
        return (v.x * v.x + v.y * v.y) / 2;
    }
}
