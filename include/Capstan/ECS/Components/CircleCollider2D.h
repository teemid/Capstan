#ifndef CAPSTAN_CIRCLE_COLLIDER_2D_H
#define CAPSTAN_CIRCLE_COLLIDER_2D_H

#include "Capstan/ECS/Components/Collider2D.h"
#include "Capstan/Math/Vector2f.h"
#include "Capstan/Common.h"


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
