#ifndef CAPSTAN_ECS_SYSTEM_H
#define CAPSTAN_ECS_SYSTEM_H


#include "Capstan/Common.h"


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
