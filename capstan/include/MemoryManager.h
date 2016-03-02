#ifndef CAPSTAN_MEMORY_MANAGER_H
#define CAPSTAN_MEMORY_MANAGER_H


#include "Platform/Types.h"


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

        void StartUp (size_t reserveSize);
        void ShutDown (void);

        void * Allocate (size_t size);
        Bool32 Free (void * memory);
    private:
        void * top;
        void * current;
        void * end;
        void * start;
    };
}


#endif
