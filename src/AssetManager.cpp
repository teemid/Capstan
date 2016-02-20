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

        asset.source = (char *)Core::Malloc((size_t)asset.size);

        FileSystem::Read(&file, (void *)asset.source, file.size);

        FileSystem::Close(&file);

        return asset;
    }
}
