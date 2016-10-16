#ifndef CAPSTAN_ENTITY_MANAGER_H
#define CAPSTAN_ENTITY_MANAGER_H


#include "Capstan/Common.h"


namespace Capstan
{
namespace ECS
{
    typedef UInt32 Entity;

    class Capstan
    {
    public:
        Component * GetComponent (Entity entity, ComponentType type);
        void AddComponent (Entity entity, ComponentType type);

        Entity AddEntity (void);
        void RemoveEntity (Entity entity);
    private:
        Entity * entities;
        Entity currentId;
    };
}
}



#endif
