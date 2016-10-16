#include "Capstan/Math/Vector2f.h"


namespace Capstan
{
    Vector2f::Vector2f (void) : x(0), y(0) { };

    Vector2f::Vector2f (Real32 x) : x(x), y(x) { };

    Vector2f::Vector2f (Real32 x, Real32 y) : x(x), y(y) { };
}
