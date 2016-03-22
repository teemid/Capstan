#ifndef CAPSTAN_ECS_SPRITE_RENDERER_COMPONENT_H
#define CAPSTAN_ECS_SPRITE_RENDERER_COMPONENT_H


// #include "ECS/Components/Component.h"


namespace Capstan
{
namespace ECS
{
    struct SpriteRendererComponent
    {
        Sprite * sprite;
        Vector2f coordinates;
    };
}
}

#endif
