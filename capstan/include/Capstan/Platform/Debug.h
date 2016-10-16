#ifndef CAPSTAN_DEBUG_H
#define CAPSTAN_DEBUG_H

#include <cstdio>


namespace Capstan
{
namespace Debug
{
    #ifdef CAPSTAN_DEBUG

    void Print (char * formattedString, ...);

    #endif
}
}


#endif
