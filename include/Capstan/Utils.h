#ifndef CAPSTAN_UTILS_H
#define CAPSTAN_UTILS_H


namespace Capstan
{
    #define ArrayLength(array) sizeof(array) / sizeof(array[0])

    #define internal static
    #define global extern

    #define KB(size) ((size) * 1024L)
    #define MB(size) (KB(size) * 1024L)
    #define GB(size) (MB(size) * 1024L)
}


#endif
