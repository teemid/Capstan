#include "AssetManager.h"

#include "Platform/Assert.h"
#include "Platform/Debug.h"
#include "Platform/FileSystem.h"
#include "Platform/Memory.h"

#include "strings.h"
#include "SystemManager.h"
#include "utils.h"


namespace Capstan
{
    AssetManager::AssetManager (void) { };
    AssetManager::~AssetManager (void) { };

    void AssetManager::StartUp (size_t size)
    {
        this->current = 0;
    }

    void AssetManager::ShutDown (void) { }

    void AssetManager::LoadResource (char * filename)
    {

    }

    ShaderAsset AssetManager::LoadShader (char * filename)
    {
        ShaderAsset asset = {};
        FileSystem::File file;
        FileSystem::Open(filename, &file);

        asset.size = file.size;

        asset.source = (char *)Memory::Allocate((size_t)asset.size);

        FileSystem::Read(&file, (void *)asset.source, file.size);

        FileSystem::Close(&file);

        return asset;
    }

    struct BMPHeader
    {
        char signature[2];
        Int32 fileSize;
        Int16 reserved[2];
        Int32 pixelArrayOffset;
    };

    struct BitmapV5Header
    {
        UInt32 DIBHeaderSize;
        Int32 width;
        Int32 height;
        Int16 Planes;
        Int16 Bits;
        UInt32 compression;
        UInt32 imageSize;
        Int32 xPixelsPerMeter;
        Int32 yPixelsPerMeter;
        UInt32 ColorTable;
        UInt32 ImportantColorCount;
        UInt32 RedChannelBitMask;
        UInt32 GreenChannelBitMask;
        UInt32 BlueChannelBitMask;
        UInt32 AlphaChannelBitMask;
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

    ImageAsset AssetManager::LoadTexture (char * filename)
    {
        ImageAsset asset = {};
        FileSystem::File file;
        FileSystem::Open(filename, &file);

        BMPHeader fileHeader = {};

        FileSystem::Read(&file, (void *)&fileHeader, sizeof(BMPHeader));

        char signature[2] = { 'B', 'M' };
        assert(String::Compare(fileHeader.signature, signature, ArrayLength(signature)));

        Debug::OutputString("BMP FileHeader");
        Debug::OutputString("Signature: %X", fileHeader.signature);
        Debug::OutputString("Size: %X", fileHeader.fileSize);
        Debug::OutputString("PixelArrayOffset: %X", fileHeader.pixelArrayOffset);

        BitmapV5Header bitmapHeader = {};

        FileSystem::Read(&file, (void *)&bitmapHeader, sizeof(BitmapV5Header));

        Debug::OutputString("BitmapV5Header:");
        Debug::OutputString("Width: %d", bitmapHeader.width);
        Debug::OutputString("Width: %d", bitmapHeader.height);

        return asset;
    }
}
