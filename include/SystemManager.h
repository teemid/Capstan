#ifndef CAPSTAN_SYSTEM_MANAGER_H
#define CAPSTAN_SYSTEM_MANAGER_H

#include "Platform/FileSystem.h"

#include "AssetManager.h"
#include "MemoryManager.h"
#include "RenderManager.h"
#include "types.h"


namespace Capstan
{
namespace System
{
    enum class Type
    {
        Asset,
        FileSystem,
        Memory,
        Renderer
    };

    internal RenderManager gRenderManager;
    internal MemoryManager gMemoryManager;
    internal AssetManager gAssetManager;
    internal FileSystem gFileSystem;

    void * Get (Type system);
    Bool32 Start (Type system, ...);
    Bool32 ShutDown (Type system);
}
}


#endif
