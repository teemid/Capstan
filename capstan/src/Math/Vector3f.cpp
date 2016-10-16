#include "Capstan/Math/Vector3f.h"


namespace Capstan
{
    Vector3f::Vector3f (void) : x(0), y(0), z(0) { };

    Vector3f::Vector3f (Real32 x) : x(x) { };

    Vector3f::Vector3f (Real32 x, Real32 y, Real32 z) : x(x), y(y), z(z) { };

    Vector3f::Vector3f (Vector2f & v) : x(v.x), y(v.y), z(0.0f) { };

    Vector3f::Vector3f (Vector2f & v, Real32 f) : x(v.x), y(v.y), z(f) { };
}
