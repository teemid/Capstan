#include "strings.h"


namespace Capstan
{
    Bool32 Compare (const char * s1, const char * s2)
    {
        Int32 i = 0;

        while (s1[i] != '\0')
        {
            if (s1[i] != s2[i])
            {
                return false;
            }
            i++;
        }

        return (s2[i] != '\0');
    }

    Bool32 Find (const char * string, const char * pattern)
    {
        Int32 i = 0;
        Int32 j = 0;
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
}
