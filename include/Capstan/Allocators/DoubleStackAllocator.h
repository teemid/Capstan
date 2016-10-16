#ifndef CAPSTAN_ALLOCATORS_DOUBLE_STACK
#define CAPSTAN_ALLOCATORS_DOUBLE_STACK


#include "Capstan/Allocators/StackAllocator.h"


namespace Capstan
{
    class DoubleStackAllocator
    {
    public:
        DoubleStackAllocator (size_t size);
        ~DoubleStackAllocator (void);

        StackAllocation Allocate (size_t size);
        StackAllocation AllocateAligned (size_t size, size_t alignment);
        void Free (StackAllocation allocation);
    private:
        void * bottom;
        void * top;
        StackMarker bottomMarker;
        StackMarker topMarker;
    };
}


#endif
