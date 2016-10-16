#ifndef CAPSTAN_GRAPHICS_SOFTWARE_H
#define CAPSTAN_GRAPHICS_SOFTWARE_H


#include "Capstan/Graphics/Renderer.h"


namespace Capstan
{
namespace Graphics
{
    class SoftwareRenderer : public Capstan::Renderer
    {
    public:
        SoftwareRenderer (void);
        ~SoftwareRenderer (void);

        void StartUp (void) override;
        void ShutDown (void) override;
        void Render (void) override;
    };
}
}


#endif
