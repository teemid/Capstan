#ifndef CAPSTAN_FILESYSTEM_H
#define CAPSTAN_FILESYSTEM_H


#include "types.h"


namespace Capstan
{
    Int64 GetFileSize (char * filename);
    void Read (char * filename, void * buffer, size_t size);
    void Write (char * filename, void * buffer, size_t size);
}


#endif
