#include "Capstan/Platform/Assert.h"
#include "Capstan/Platform/Debug.h"
#include "Capstan/Platform/FileSystem.h"
#include "Capstan/Platform/Memory.h"

#include "Capstan/BitmapFile.h"
#include "Capstan/Strings.h"
#include "Capstan/Utils.h"

#include "Capstan/AssetManager.h"


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

    ImageAsset AssetManager::LoadTexture (char * filename)
    {
        ImageAsset asset = {};
        FileSystem::File file;
        FileSystem::Open(filename, &file);

        BitmapCoreHeader fileHeader = {};

        FileSystem::Read(&file, (void *)&fileHeader, sizeof(BitmapCoreHeader));

        char signature[2] = { 'B', 'M' };
        assert(String::Compare(fileHeader.signature, signature, ArrayLength(signature)));

        BitmapInfoHeader bitmapHeader = {};

        FileSystem::Read(&file, (void *)&bitmapHeader, sizeof(BitmapInfoHeader));

        asset.width = bitmapHeader.width;
        asset.height = bitmapHeader.height;
        Int32 bytes = fileHeader.fileSize - fileHeader.pixelArrayOffset;
        asset.data = Memory::Allocate((size_t)bytes);

        FileSystem::Read(&file, asset.data, bytes);

        FileSystem::Close(&file);

        return asset;
    }
}
