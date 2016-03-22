#ifndef CAPSTAN_CIRCLE_COLLIDER_2D_H
#define CAPSTAN_CIRCLE_COLLIDER_2D_H

#include "ECS/Components/Collider2D.h"
#include "Math/Vector2f.h"
#include "Platform/Types.h"


namespace Capstan
{
namespace ECS
{
    struct CircleCollider2D : Collider2D
    {
        Vector2f center;
        Real32 radius;
    };
}
}


#endif
