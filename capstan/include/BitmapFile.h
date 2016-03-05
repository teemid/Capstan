#ifndef CAPSTAN_BITMAP_H
#define CAPSTAN_BITMAP_H


#include "Platform/Types.h"


namespace Capstan
{
    enum class Compression : UInt32
    {
        RGB = 0x1,
        BITFIELDS = 0x3
    };

    #pragma pack(push, 1)

    struct BitmapCoreHeader
    {
        char signature[2];
        Int32 fileSize;
        Int16 reserved[2];
        Int32 pixelArrayOffset;
    };


    struct BitmapInfoHeader
    {
        UInt32 headerSize;
        Int32  width;
        Int32  height;
        Int16  planes;
        Int16  bitsPerPixel;
        Compression compression;
        UInt32 imageSize;
        Int32  xPixelsPerMeter;
        Int32  yPixelsPerMeter;
        UInt32 colorIndexCount;
        UInt32 requiredColorIndexes;
    };


    struct BitmapInfoV5Header
    {
        UInt32 headerSize;
        Int32 width;
        Int32 height;
        Int16 planes;
        Int16 bitsPerPixel;
        UInt32 compression;
        UInt32 imageSize;
        Int32 xPixelsPerMeter;
        Int32 yPixelsPerMeter;
        UInt32 colorIndexCount;
        UInt32 requiredColorIndexes;
        UInt32 redChannelBitMask;
        UInt32 greenChannelBitMask;
        UInt32 blueChannelBitMask;
        UInt32 alphaChannelBitMask;
        UInt32 ColorSpaceType;
        // NOTE (Emil): CIE Triple, Each CIE is a (x,y,z) point in CIE colorspace.
        Int32 CIEEndpoints[9];
        // NOTE (Emil): Red, Green, and Blue gamma channels
        UInt32 gamma[3];
        UInt32 intent;
        UInt32 profileData;
        UInt32 profileSize;
        UInt32 reserved;
    };

    #pragma pack(pop)
}

#endif
