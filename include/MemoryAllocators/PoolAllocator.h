#include "Platform/Memory.h"


namespace Capstan
{
    template <typename T>
    class PoolAllocator
    {
    public:
        PoolAllocator (size_t size);
        ~PoolAllocator (void);

        void * Allocate ();
        void Free (void * memory);
    private:
        T * freeList;
        T * pool;
        size_t size;
    };
}
