#include "Capstan/Platform/Assert.h"
#include "Capstan/Platform/Memory.h"

#include "Capstan/Allocators/BitmappedAllocator.h"


namespace Capstan
{
    BitmappedAllocator::BitmappedAllocator (size_t size, size_t blockSize)
    {
        this->blockSize = blockSize;
        this->memory = Memory::Allocate(size);
        Assert(this->memory, "Failed to allocate memory.\n");
        // NOTE (Emil): We allocate one bit per block in the allocator.
        this->occupied = Memory::Allocate((size / blockSize) / 8);
    }

    BitmappedAllocator::~BitmappedAllocator (void)
    {
        Memory::Free(this->memory);
        Memory::Free(this->occupied);
    }

    void * BitmappedAllocator::Allocate (size_t size)
    {
        Byte * byte = (Byte *)this->memory;

        return nullptr;
    }

    void BitmappedAllocator::Deallocate (void * memory)
    {
    }
}

