#ifndef CAPSTAN_MEMORY_MANAGER_H
#define CAPSTAN_MEMORY_MANAGER_H

#include "Capstan/Types.h"


namespace Capstan
{
    enum class ManagerType
    {
        StackAllocator,
        DoubleStackAllocator,
        PoolAllocator
    };

    class MemoryManager
    {
    public:
        MemoryManager ();
        ~MemoryManager ();

        void StartUp (UInt64 reserveSize);
        void ShutDown (void);

        void * Allocate (UInt64 size);
        Bool32 Free (void * memory);
    private:
        void * top;
        void * current;
        void * end;
        void * start;
    };
}


#endif
