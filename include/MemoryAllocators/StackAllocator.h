#ifndef CAPSTAN_MEMORY_STACK_ALLOCATOR_H
#define CAPSTAN_MEMORY_STACK_ALLOCATOR_H


#include "types.h"


namespace Capstan
{
    typedef UInt32 StackMarker;

    struct StackAllocation
    {
        void * memory;
        StackMarker marker;
    };

    class StackAllocator
    {
    public:
        StackAllocator (UInt64 size);
        ~StackAllocator (void);

        StackAllocation Allocate (UInt32 size);
        void Free (StackAllocation allocation);
    private:
        void * start;
        void * end;
        StackMarker marker;
    };
}


#endif
