#ifndef CAPSTAN_MATRIX_H
#define CAPSTAN_MATRIX_H


#include "types.h"


namespace Capstan
{
    class Matrix4
    {
    public:
        Real32 Cross (Matrix4 * rhs);
    private:
        Real32 data[16];
    };
}


#endif
