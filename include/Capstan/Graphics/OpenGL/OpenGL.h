#ifndef CAPSTAN_GRAPHICS_OPENGL_H
#define CAPSTAN_GRAPHICS_OPENGL_H

#include "gl/glcorearb.h"

#include "Capstan/Graphics/Renderer.h"

#define CAPSTAN_GL(type, name) extern type name;
#include "Capstan/Graphics/OpenGL/Functions.def"


namespace Capstan
{
namespace Graphics
{
    class Shader;

    class OpenGL : public Capstan::Renderer
    {
    public:
        explicit OpenGL (void);
        ~OpenGL (void);

        void StartUp (void) override;
        void ShutDown (void) override;
        void Render (void) override;
    private:
        Shader * shader;
    };
}
}

#endif
