#ifndef CAPSTAN_CONTAINERS_DYNAMIC_ARRAY_H
#define CAPSTAN_CONTAINERS_DYNAMIC_ARRAY_H


#include "Platform/Memory.h"


#define Increment(variable) (variable) += 1
#define Decrement(variable) (variable) -= 1


namespace Capstan
{
    #define DEFAULT_INITIAL_SIZE 24

    template<typename T>
    class DynamicArray
    {
    public:
        DynamicArray (void);
        DynamicArray (UInt32 initialSize);
        ~DynamicArray (void);

        void Append (T item);
        void Insert (T item, UInt32 position);
        void Remove (T item);

        void Resize (UInt32 size);

        UInt32 Length (void);

        T & operator [](UInt32 index);
    private:
        T * memory;
        UInt32 size;
        UInt32 length;
    };

    template<typename T>
    DynamicArray::DynamicArray (void)
    {
        memory = (T *)Memory::Allocate(DEFAULT_INITIAL_SIZE);
        size = DEFAULT_INITIAL_SIZE;
        length = 0;
    }

    template<typename T>
    DynamicArray::DynamicArray (UInt32 initial)
    {
        memory = (T *)Memory::Allocate(initial);
        length = 0;
        size = initial;
    }

    DynamicArray::~DynamicArray (void)
    {
        Memory::Free((void *)memory);
    }

    template<typename T>
    void DynamicArray::Append (T item)
    {
        if (length == size)
        {
            Resize(size * 2);
        }

        *(memory + length) = item;
        Increment(length);
    }

    template<typename T>
    void DynamicArray::Insert (T item, UInt32 position)
    {
        if (length == size)
        {
            Resize(size * 2);
        }

        Memory::Copy(memory + position, memory + position + 1, length - position);
        *(memory + position) = item;
        Increment(length);
    }

    template<typename T>
    void DynamicArray::Remove (UInt32 position)
    {
        Memory::Copy(memory + position + 1, memory + position, length - position);
        Decrement(length);
    }

    template<typename T>
    void DynamicArray::Resize (UInt32 size)
    {
        memory = (T *)Memory::Reallocate(memory, this->size, size);
    }

    UInt32 DynamicArray::Length (void)
    {
        return length;
    }

    template<typename T>
    T & DynamicArray::operator [](UInt32 index)
    {
        return *(memory + index);
    }
}


#endif
