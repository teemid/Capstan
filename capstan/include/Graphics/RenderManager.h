#ifndef CAPSTAN_GRAPHICS_RENDER_MANAGER_H
#define CAPSTAN_GRAPHICS_RENDER_MANAGER_H


#include "Graphics/Renderer.h"


namespace Capstan
{
namespace Graphics
{
    class RenderManager
    {
    public:
        RenderManager (void);
        ~RenderManager (void);

        void StartUp (void);
        void ShutDown (void);
        void Render (void);
    private:
        Renderer * renderer;
    };
}
}


#endif
