#ifndef CAPSTAN_ECS_SYSTEM_H
#define CAPSTAN_ECS_SYSTEM_H


#include "Platform/Types.h"


namespace Capstan
{
namespace ECS
{
    class System
    {
    public:
        virtual void Update (Real64 deltaTime) = 0;
    };
}
}


#endif
