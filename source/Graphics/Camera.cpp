#include "Capstan/Graphics/Camera.h"


namespace Capstan
{
namespace Graphics
{
    Camera::Camera(void) { }

    Camera::Camera(Vector3f position, Vector3f direction)
    {
        this->position = position;
        this->direction = direction;
    }

    Camera::~Camera(void) { }
}
}
