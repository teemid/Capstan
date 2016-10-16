#ifndef CAPSTAN_COLOR_H
#define CAPSTAN_COLOR_H


namespace Capstan
{
    struct Color3f
    {
        union
        {
            Real32 data[3];
            struct
            {
                Real32 r;
                Real32 g;
                Real32 b;
            };
        };
    };

    inline Lerp (Color3f start, Color3f end, Real32 t);

    struct Color4f
    {
        union
        {
            Real32 data[4];
            struct
            {
                Real32 r;
                Real32 g;
                Real32 b;
                Real32 a;
            };
        };
    };
}


#endif
