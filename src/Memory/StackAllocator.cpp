#include "assert.h"
#include "debug.h"
#include "memory.h"
#include "Memory/StackAllocator.h"


namespace Capstan
{
    StackAllocator::StackAllocator (Int64 size)
    {
        this->memory = Core::Malloc(size);
        this->top = this->memory;
        this->end = (void * )((Byte *)this->memory + size);
    }

    StackAllocator::~StackAllocator (void)
    {
        Core::Free(this->memory);
    }

    StackAllocation StackAllocator::Allocate (Int64 size)
    {
        if (((Byte *)this->memory + size) - (Byte *)this->top < size)
        {
            Debug::OutputString("StackAllocator out of memory");

            assert(false);
        }

        StackAllocation allocation;
        allocation.memory = this->top;
        allocation.top = (void *)((Byte *)this->memory + size);

        this->top = allocation.top;

        return allocation;
    }

    void StackAllocator::Free (StackAllocation allocation)
    {
        if (allocation.top != this->top)
        {
            Debug::OutputString("StackAllocator cannot free memory that is not on the top of the stack.");

            assert(false);
        }

        this->top = allocation.memory;
    }
}
