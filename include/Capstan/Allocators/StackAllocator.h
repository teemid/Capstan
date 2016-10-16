#ifndef CAPSTAN_MEMORY_STACK_ALLOCATOR_H
#define CAPSTAN_MEMORY_STACK_ALLOCATOR_H


#include "Capstan/Types.h"


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
        StackAllocator (size_t size);
        ~StackAllocator (void);

        StackAllocation Allocate (size_t size);
        StackAllocation AllocateAligned (size_t size, size_t alignment);
        void Free (StackAllocation allocation);
    private:
        void * start;
        void * end;
        StackMarker marker;
    };
}


#endif
