#ifndef CAPSTAN_GLOBALS_H
#define CAPSTAN_GLOBALS_H


#include "AssetManager.h"
#include "InputManager.h"
#include "MemoryManager.h"
#include "Timer.h"
#include "Graphics/RenderManager.h"
#include "Platform/FileSystem.h"



namespace Capstan
{
    extern AssetManager            gAssetManager;
    extern FileSystem              gFileSystem;
    extern InputManager            gInputManager;
    extern MemoryManager           gMemoryManager;
    extern Graphics::RenderManager gRenderManager;
    extern Timer                   gTimer;
}


#endif
