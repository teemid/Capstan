#ifndef CAPSTAN_ECS_COMPONENTS_BOX_COLLIDER_2D_H
#define CAPSTAN_ECS_COMPONENTS_BOX_COLLIDER_2D_H


#include "ECS/Components/Collider2D.h"
#include "Math/Vector2f.h"


namespace Capstan
{
namespace ECS
{
    struct BoxCollider2D : Collider2D
    {
        Vector2f lower;
        Vector2f upper;
    };
}
}

#endif
