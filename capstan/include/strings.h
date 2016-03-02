#ifndef CAPSTAN_STRINGS_H
#define CAPSTAN_STRINGS_H

#include "Platform/Types.h"


namespace Capstan
{
namespace String
{
    Bool32 Compare (const char * s1, const char * s2);

    Bool32 Compare (const char * s1, const char * s2, UInt32 lenght = 0);

    Bool32 Find (const char * string, const char * pattern);
}
}


#endif
