#ifndef CAPSTAN_PHYSICS_2D_SYSTEM_H
#define CAPSTAN_PHYSICS_2D_SYSTEM_H


#include "Capstan/ECS/Systems/System.h"
#include "Capstan/ECS/Components/Collider2D.h"
#include "Capstan/ECS/Components/BoxCollider2D.h"
#include "Capstan/ECS/Components/CircleCollider2D.h"


namespace Capstan
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
