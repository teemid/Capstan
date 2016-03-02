#include "Allocators/BitmappedAllocator.h"

#include "Platform/Assert.h"
#include "Platform/Memory.h"


namespace Capstan
{
    BitmappedAllocator::BitmappedAllocator (size_t size, size_t blockSize)
    {
        this->blockSize = blockSize;
        this->memory = Memory::Allocate(size);
        assert(this->memory);
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

