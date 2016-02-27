#include "RenderManager.h"
#include "OpenGL/OpenGL.h"


namespace Capstan
{
    RenderManager::RenderManager (void) { };
    RenderManager::~RenderManager (void) { };

    void RenderManager::StartUp (void)
    {
        renderer = new OpenGL();
        renderer->StartUp();
    }

    void RenderManager::ShutDown (void)
    {
        renderer->ShutDown();
        delete renderer;
    }

    void RenderManager::Render (void)
    {
        renderer->Render();
    }
}
