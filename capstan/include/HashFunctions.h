#ifndef CAPSTAN_HASH_H
#define CAPSTAN_HASH_H


#include "Platform/Types.h"


namespace Capstan
{
    Hash MultiplicativeHashFunction (UInt8 * bytes, UInt32 length)
    {
        Hash hash = 0;

        for (UInt32 i = 0; i < length; ++i)
        {
            hash = ((hash * 31) + bytes[i]) % 17;
        }

        return hash;
    };


    Hash djb2HashFunction (UInt8 * bytes, UInt32 length)
    {
        Hash hash = 5381;

        Int32 c;

        while (c = *bytes++)
        {
            hash = ((hash << 5) + hash) + c;
        }

        return hash;
    }
}


#endif
