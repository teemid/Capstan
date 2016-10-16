#ifndef CAPSTAN_PLATFORM_OPENGL_CONTEXT_H
#define CAPSTAN_PLATFORM_OPENGL_CONTEXT_H


#include "Capstan/Types.h"


namespace Capstan
{
namespace Platform
{
    Bool32 CreateContext(void);
    Bool32 DeleteContext(void);

    void * GetFunctionAddress(char * name);

    Bool32 SwapBuffers (void);
}
}

#endif
