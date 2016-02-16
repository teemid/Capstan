#ifndef CAPSTAN_MEMORY_MANAGER_H
#define CAPSTAN_MEMORY_MANAGER_H


#include "types.h"


namespace Capstan
{
    class MemoryManager
    {
    public:
        MemoryManager ();
        ~MemoryManager ();

        void StartUp (size_t reserveSize);
        void ShutDown (void);

        Bool32 Allocate (void * memory, size_t size);
        Bool32 Free (void * memory);
    private:
        void * top;
        void * current;
        void * end;
        void * start;
    };
}


#endif
