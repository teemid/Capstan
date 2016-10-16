#ifndef CAPSTAN_ALLOCATORS_BITMAPPED_BLOCK_H
#define CAPSTAN_ALLOCATORS_BITMAPPED_BLOCK_H


namespace Capstan
{
    class BitmappedAllocator
    {
    public:
        BitmappedAllocator (size_t size, size_t blockSize);
        ~BitmappedAllocator (void);

        void * Allocate (size_t size);
        void Deallocate (void * memory);
    private:
        void * memory;
        void * occupied;
        size_t blockSize;
    };
}


#endif
