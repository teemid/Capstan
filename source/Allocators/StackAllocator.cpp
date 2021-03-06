#include "Capstan/Platform/Assert.h"
#include "Capstan/Platform/Debug.h"
#include "Capstan/Platform/Memory.h"

#include "Capstan/Allocators/StackAllocator.h"


namespace Capstan
{
    StackAllocator::StackAllocator (size_t size)
    {
        this->start = Memory::Allocate((size_t)size);
        this->marker = 0;
        this->end = (void *)((Byte *)this->start + size);
    }

    StackAllocator::~StackAllocator (void)
    {
        Memory::Free(this->start);
    }

    StackAllocation StackAllocator::Allocate (size_t size)
    {
        size_t freeBytes = (Byte *)this->end - ((Byte *)this->start + this->marker);

        Assert((freeBytes < size), "StackAllocator out of memory.\n");

        StackAllocation allocation;
        allocation.memory = this->start;
        this->marker += (UInt32)size;
        allocation.marker = this->marker;

        return allocation;
    }

    // NOTE (Emil): Alignment must be a power of 2, typically 4 or 16.
    StackAllocation StackAllocator::AllocateAligned (size_t size, size_t alignment)
    {
        StackAllocation allocation = { };

        Assert((alignment & (alignment - 1)) == 0, "StackAllocator alignment error.\n");

        size_t expanded = size + alignment;

        StackAllocation unalignedAllocation = this->Allocate(expanded);
        uintptr_t rawAddress = reinterpret_cast<uintptr_t>(unalignedAllocation.memory);

        size_t mask = (alignment - 1);

        uintptr_t misalignment = (rawAddress & mask);

        ptrdiff_t adjustment = alignment - misalignment;

        allocation.memory = reinterpret_cast<void *>(rawAddress + adjustment);
        allocation.marker = unalignedAllocation.marker;

        return allocation;
    }

    void StackAllocator::Free (StackAllocation allocation)
    {
        Assert(allocation.marker != this->marker, "StackAllocator cannot free memory that is not on the top of the stack.\n");

        this->marker = (UInt32)((Byte *)allocation.memory - (Byte *)this->start);
    }
}
