#ifndef CAPSTAN_OPENGL_H
#define CAPSTAN_OPENGL_H


#include "OpenGL/gl.h"
#include "RenderManager.h"
#include "OpenGL/Shader.h"


namespace Capstan
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


#endif
