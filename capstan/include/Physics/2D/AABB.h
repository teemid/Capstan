#ifndef CAPSTAN_PHYSICS_2D_AABB
#define CAPSTAN_PHYSICS_2D_AABB


#include "Math/Vector2f.h"


#include "Platform/Types.h"


namespace Capstan
{
namespace Physics
{
    struct AABB
    {
        Vector2f lower;
        Vector2f upper;
    };

    Bool32 Collision(AABB body1, AABB body2);
}
}


#endif
