#ifndef CAPSTAN_GRAPHICS_RENDERER_H
#define CAPSTAN_GRAPHICS_RENDERER_H


namespace Capstan
{
    class Renderer
    {
    public:
        virtual void StartUp (void) = 0;
        virtual void ShutDown (void) = 0;
        virtual void Render (void) = 0;
    };
}


#endif
