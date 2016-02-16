#include "assert.h"
#include "types.h"
#include "memory.h"


namespace Capstan
{
namespace Core
{
    StackAllocator::StackAllocator (size_t initial_size)
    {
        this->memory = Malloc(initial_size);
        this->top = this->memory;
        this->size = (UInt8 *)this->memory + initial_size;

        assert((UInt8 *)this->size - (UInt8 *)this->memory == initial_size);
    }

    void * StackAllocator::Alloc (size_t size)
    {
        if (size == 0)
        {
            // NOTE (Emil): No memory to allocate.
            return 0;
        }
        // NOTE (Emil): Ran out of memory.
        else if (size > (size_t)((uint8_t *)this->size - (uint8_t *)this->top))
        {
            return 0;
        }

        void * memory = this->top;
        this->top = ((uint8_t *)this->top + size);

        return memory;
    }

    void StackAllocator::Free (void * memory)
    {
        if (!memory)
        {
            // NOTE (Emil): No memory to free!
        }

        if (memory != this->top)
        {
            // NOTE (Emil): Can't deallocate memory that isn't at the top of the stack.
        }

        Capstan::Core::Free(memory);

        assert(memory == 0);
    }
}
}
