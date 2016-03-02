#ifndef CAPSTAN_RENDER_MANAGER_H
#define CAPSTAN_RENDER_MANAGER_H

#include "Renderer.h"


namespace Capstan
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


#endif
