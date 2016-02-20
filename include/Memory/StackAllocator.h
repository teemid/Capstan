#ifndef CAPSTAN_MEMORY_STACK_ALLOCATOR_H
#define CAPSTAN_MEMORY_STACK_ALLOCATOR_H


#include "types.h"


namespace Capstan
{
    struct StackAllocation
    {
        void * memory;
        void * top;
    };


    class StackAllocator
    {
    public:
        StackAllocator (Int64 size);
        ~StackAllocator (void);

        StackAllocation Allocate (Int64 size);
        void Free (StackAllocation allocation);
    private:
        void * memory;
        void * top;
        void * end;
    };
}


#endif
