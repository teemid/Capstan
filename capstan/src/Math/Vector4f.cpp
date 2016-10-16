#include "Capstan/Math/Vector4f.h"


namespace Capstan
{
    Vector4f::Vector4f (void) { }

    Vector4f::Vector4f (Real32 x) : x(x), y(x), z(x), w(x) { }

    Vector4f::Vector4f (Real32 x, Real32 y, Real32 z) : x(x), y(y), z(z) { }

    Vector4f::Vector4f (Real32 x, Real32 y, Real32 z, Real32 w) : x(x), y(y), z(z), w(w) { };
}
