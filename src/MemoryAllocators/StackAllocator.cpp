#include "MemoryAllocators/StackAllocator.h"

#include "Platform/Assert.h"
#include "Platform/Debug.h"
#include "Platform/Memory.h"


namespace Capstan
{
    StackAllocator::StackAllocator (UInt64 size)
    {
        this->start = Memory::Allocate((size_t)size);
        this->marker = 0;
        this->end = (void *)((Byte *)this->start + size);
    }

    StackAllocator::~StackAllocator (void)
    {
        Memory::Free(this->start);
    }

    StackAllocation StackAllocator::Allocate (UInt32 size)
    {
        UInt64 freeBytes = (Byte *)this->end - ((Byte *)this->start + this->marker);
        // UInt64 freeBytes = freeMemory * 4; // NOTE (Emil): A pointer is 64 bit = 4 bytes
        if (freeBytes < size)
        {
            Debug::OutputString("StackAllocator out of memory");

            assert(false);
        }

        StackAllocation allocation;
        allocation.memory = this->start;
        this->marker += size;
        allocation.marker = this->marker;

        return allocation;
    }

    void StackAllocator::Free (StackAllocation allocation)
    {
        if (allocation.marker != this->marker)
        {
            Debug::OutputString("StackAllocator cannot free memory that is not on the top of the stack.");

            assert(false);
        }

        this->marker = (Byte *)allocation.memory - (Byte *)this->start;
    }
}
