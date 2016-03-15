#ifndef CAPSTAN_GRAPHICS_CAMERA_H
#define CAPSTAN_GRAPHICS_CAMERA_H


#include "Math/Vector3f.h"


namespace Capstan
{
namespace Graphics
{
    class Camera
    {
    public:
        Camera (void);
        Camera (Vector3f position, Vector3f direction);
        ~Camera (void);

        void LookAt (Vector3f target);
    private:
        Vector3f position;
        Vector3f direction;
        Vector3f right;
        Vector3f up;
    };
}
}


#endif
