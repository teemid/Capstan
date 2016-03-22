#ifndef CAPSTAN_CONTAINERS_HASHMAP_H
#define CAPSTAN_CONTAINERS_HASHMAP_H


#include "Platform/Types.h"


#define Increment(variable) (variable) += 1
#define Decrement(variable) (variable) -= 1

#define DEFAULT_BUCKET_COUNT 11
#define DEFAULT_BUCKET_LENGTH 4


namespace Capstan
{
    typedef UInt32 Hash;
    typedef Hash (*HashFunction)(UInt8 bytes);

    template<typename T>
    Hash HashFunction (T item, UInt32 numberOfBytes)
    {
        Hash hash;
        UInt8 bytes = (UInt8)item;

        for (UInt32 index = 0; i < numberOfBytes; ++i)
        {
            hash += bytes[index];
        }

        return hash;
    }

    template<typename Key, typename Value>
    class HashMap
    {
    public:
        struct HashMapNode
        {
            Hash hash;
            Key key;
            Value value;
        };

        typedef DynamicArray<HashMapNode> Bucket;

        HashMap (void);
        HashMap (UInt32 bucketCount);
        HashMap (UInt32 bucketCount, UInt32 bucketLength);
        ~HashMap (void);

        void SetHashFunction (HashFunction function);

        void Add (Key key, Value value);
        Value Remove (Key key);

        UInt32 Length (void);

        Value & operator [](Key key);
        Value operator [](Key key) const;
    private:
        DynamicArray<Value> * buckets;
        HashFunction function;
        UInt32 length;
    };

    template<typename Key, typename Value>
    HashMap::HashMap (void)
    {
        buckets = (Bucket *)Memory::Allocate(sizeof(Bucket) * DEFAULT_BUCKET_COUNT);

        for (UInt32 bucket = 0; bucket < DEFAULT_BUCKET_COUNT; ++bucket)
        {
            buckets[bucket] = DynamicArray(DEFAULT_BUCKET_LENGTH);
        }
    }

    template<typename Key, typename Value>
    HashMap::HashMap (UInt32 bucketCount, UInt32 bucketLength)
    {
        buckets = (Bucket *)Memory::Allocate(sizof(Bucket) * bucketCount);

        for (UInt32 bucket = 0; bucket < bucketCount; ++bucket)
        {
            buckets[bucket] = DynamicArray(bucketLength);
        }
    }

    void SetHashFunction (HashFunction function)
    {
        function = function;
    }

    template<typename Key, typename Value>
    void HashMap::Add (Key key, Value value)
    {
        Hash hash = function(key);
        UInt32 bucket = hash % buckets.Length();
        Increment(length);
    }

    template<typename Key, typename Value>
    Value HashMap::Remove (Key key)
    {
        Hash hash = function(key);
        UInt32 bucket = hash % buckets.Length();
        Decrement(length);
    }

    UInt32 HashMap::Length (void)
    {
        return length;
    }

    template<typename Key, typename Value>
    Value & operator [](Key key)
    {
        Hash hash = function(key);
        UInt32 bucket = hash % buckets.Length();

        while (UInt32 index = 0; index < buckets[bucket].Length(); ++i)
        {
            if (key == buckets[bucket][index].key && value == buckets[bucket][index].value)
            {
                return buckets[bucket][index];
            }
        }
    }

    template<typename Key, typename Value>
    Value operator [](Key key) const
    {
        Hash hash = function(key);
        UInt32 bucket = hash % buckets.Length();

        while (UInt32 index = 0; index < buckets[bucket].Length(); ++i)
        {
            if (key == buckets[bucket][index].key && value == buckets[bucket][index].value)
            {
                return buckets[bucket][index];
            }
        }
    }
}


#endif
