#ifndef CAPSTAN_COMMON_H
#define CAPSTAN_COMMON_H

#include "Capstan/Types.h"

#define local_persist static
#define internal static

#define ILLEGAL_CASE(message, ...) \
    default: \
    { \
        Assert(false, message, __VA_ARGS__); \
    } break

#endif
