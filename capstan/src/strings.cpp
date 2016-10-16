#include "Capstan/strings.h"


namespace Capstan
{
namespace String
{
    struct String
    {
        char * string;
        UInt32 length;
    };

    Bool32 Compare (const char * s1, const char * s2, UInt32 length)
    {
        UInt32 i = 0;

        while (i < length)
        {
            if (s1[i] != s2[i])
            {
                return false;
            }

            ++i;
        }

        return true;
    }

    Bool32 Compare (const char * s1, const char * s2)
    {
        UInt32 i = 0;

        while (s1[i] != '\0')
        {
            if (s1[i] != s2[i])
            {
                return false;
            }
            i++;
        }

        return (s2[i] == '\0');
    }

    // TODO (Emil): Implement less naive version?
    Bool32 Find (const char * string, const char * pattern)
    {
        UInt32 i = 0;
        UInt32 j = 0;

        while (string[i] != '\0')
        {
            if (string[i] == pattern[0])
            {
                for (j = 1; pattern[j] != '\0'; j++)
                {
                    if (pattern[j] != string[i + j])
                    {
                        break;
                    }
                }

                return true;
            }
        }

        return false;
    }

    char ** Split (char * string, const char delimiter)
    {
        return nullptr;
    }
}
}
