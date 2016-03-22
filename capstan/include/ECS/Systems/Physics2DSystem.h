#ifndef CAPSTAN_PHYSICS_2D_SYSTEM_H
#define CAPSTAN_PHYSICS_2D_SYSTEM_H


#include "ECS/Systems/System.h"
#include "ECS/Components/Collider2D.h"
#include "ECS/Components/BoxCollider2D.h"
#include "ECS/Components/CircleCollider2D.h"


namespace Capstsan
{
namespace ECS
{
    class Physics2DSystem : public System
    {
    public:
        void Update(Real64 deltaTime);
    };
}
}

#endif
