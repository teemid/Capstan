#ifndef CAPSTAN_ECS_SPRITE_RENDERER_SYSTEM_H
#define CAPSTAN_ECS_SPRITE_RENDERER_SYSTEM_H


#include "ECS/Systems/System.h"


namespace Capstan
{
namespace ECS
{
    class SpriteRendererSystem : public System
    {
    public:
        void Update (Real64 deltaTime);
    private:
        SpriteRendererComponent
    };
}
}
