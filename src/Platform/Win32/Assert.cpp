#include <stdio.h>


#include "Platform/Assert.h"


namespace Capstan
{
    void ReportAssertFailure (char * msg, char * filename, int linenumber)
    {
        ::printf("%s %s %i", msg, filename, linenumber);
    }
}
