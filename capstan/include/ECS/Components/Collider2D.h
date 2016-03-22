#ifndef CAPSTAN_ECS_COMPONENT_COLLIDER_2D_H
#define CAPSTAN_ECS_COMPONENT_COLLIDER_2D_H


namespace Capstan
{
namespace ECS
{
    namespace Collider2DType
    {
        Box,
        Circle
    };


    struct Collider2D
    {
        Collider2DType type;
    };
}
}


#endif
