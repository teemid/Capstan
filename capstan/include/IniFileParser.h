#ifndef CAPSTAN_INIFILE_PARSER_H
#define CAPSTAN_INIFILE_PARSER_H


#include "Platform/FileSystem.h"


namespace Capstan
{
    template<typename T>
    ParseIniFile (char * filename, char * section)
    {
        File file;

        FileSystem::Open(filename, &file);

        FileSystem::Read();
    }
}


#endif
