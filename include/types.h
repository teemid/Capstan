#ifndef CAPSTAN_COMMON_H
#define CAPSTAN_COMMON_H


#include <stdint.h>


typedef uint8_t Byte;
typedef uint8_t  UInt8;
typedef uint16_t UInt16;
typedef uint32_t UInt32;
typedef uint64_t UInt64;

typedef int8_t   Int8;
typedef int16_t  Int16;
typedef int32_t  Int32;
typedef int64_t  Int64;

typedef float    Real32;
typedef double   Real64;
typedef Int32    Bool32;


#define internal static
#define local_persist static
// #define global_variable extern

#define KB(x) (x * 1024L)
#define MB(x) (KB(x) * 1024L)
#define GB(x) (MB(x) * 1024L)


#endif
