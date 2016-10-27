#ifndef CAPSTAN_PLATFORM_OPENGL_CONTEXT_H
#define CAPSTAN_PLATFORM_OPENGL_CONTEXT_H

#include "Capstan/Types.h"


namespace Capstan
{
namespace Platform
{
    struct PlatformData;

    namespace OpenGL
    {
        Bool32 CreateContext (PlatformData * data, Int32 major_version, Int32 minor_version);
        Bool32 DeleteContext (PlatformData * data);
        Bool32 SwapBuffers (PlatformData * data);

        void * GetFunctionAddress (char * name);
    }
}
}

#endif
