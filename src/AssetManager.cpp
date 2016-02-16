#include "assets.h"
#include "AssetManager.h"

#include "FileSystem.h"
#include "memory.h"
#include "SystemManager.h"


namespace Capstan
{
    AssetManager::AssetManager (void) { };
    AssetManager::~AssetManager (void) { };

    void AssetManager::StartUp (size_t size)
    {
        MemoryManager * gMemoryManager = (MemoryManager *)System::Get(System::Type::Memory);

        gMemoryManager->Allocate(assets, size);

        this->current = 0;
    }

    void AssetManager::ShutDown (void)
    {
        MemoryManager * gMemoryManager = (MemoryManager *)System::Get(System::Type::Memory);

        gMemoryManager->Free(assets);
    }

    void AssetManager::LoadResource (char * filename)
    {

    }

    ShaderAsset AssetManager::LoadShader (char * filename)
    {
        ShaderAsset asset = {};
        asset.size = GetFileSize(filename);

        asset.source = (char *)Core::Malloc(asset.size);

        Read(filename, (void *)asset.source, asset.size);

        return asset;
    }
}
