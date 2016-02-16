#ifndef CAPSTAN_SYSTEM_MANAGER_H
#define CAPSTAN_SYSTEM_MANAGER_H


#include "AssetManager.h"
#include "debug.h"
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
        Memory,
        Renderer
    };

    internal RenderManager gRenderManager;
    internal MemoryManager gMemoryManager;
    internal AssetManager gAssetManager;

    void * Get (Type system);
    Bool32 Start (Type system, ...);
    Bool32 ShutDown (Type system);
}
}


#endif
