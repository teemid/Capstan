#ifndef CAPSTAN_GRAPHICS_OPENGL_H
#define CAPSTAN_GRAPHICS_OPENGL_H

#include "Graphics/OpenGL/gl.h"
#include "Graphics/OpenGL/Shader.h"
#include "Graphics/Renderer.h"

namespace Capstan
{
namespace Graphics
{
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
