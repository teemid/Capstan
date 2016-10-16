#include "Capstan/Graphics/RenderManager.h"
#include "Capstan/Graphics/OpenGL/OpenGL.h"


namespace Capstan
{
namespace Graphics
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
}
