#ifndef CAPSTAN_TEXTURE_H
#define CAPSTAN_TEXTURE_H

namespace Capstan
{
    class Texture
    {
    public:
        enum class WrapMode
        {
            WRAP_CLAMP,
            WRAP_CLAMP_ZERO,
            WRAP_REPEAT,
            WRAP_MIRRORED_REPEAT,
            WRAP_MAX_ENUM
        };

        enum class FilterMode
        {
            FILTER_NONE,
            FILTER_LINEAR,
            FILTER_NEAREST,
            FILTER_MAX_ENUM
        };

        struct Wrap
        {
            WrapMode s;
            WrapMode t;
        };

        Texture (void);
        ~Texture (void);
    private:
    };
}

#endif
