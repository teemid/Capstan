#ifndef CAPSTAN_DEBUG_H
#define CAPSTAN_DEBUG_H

#include <stdio.h>


namespace Capstan
{
namespace Debug
{
    #ifdef CAPSTAN_DEBUG

    void OutputString (char * formattedString, ...);

    #define Print(string, ...) Capstan::Debug::OutputString(string, ##__VA_ARGS__);

    #else

    #define Print(string, ...)

    #endif
}
}


#endif
