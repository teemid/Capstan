#ifndef CAPSTAN_GLOBALS_H
#define CAPSTAN_GLOBALS_H

#include "Capstan/AssetManager.h"
#include "Capstan/InputManager.h"
#include "Capstan/MemoryManager.h"
#include "Capstan/Timer.h"
#include "Capstan/Graphics/RenderManager.h"
#include "Capstan/Platform/FileSystem.h"


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
