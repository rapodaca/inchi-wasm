#include <string.h>
#include <time.h>
#include "inchi_api.h"

size_t molfile_to_inchi(char *molfile, char *options, char *result)
{
    inchi_Output output;
    int status = MakeINCHIFromMolfileText(molfile, options, &output);

    if (status == 0 || status == 1) {
      strcpy(result, output.szInChI);
    } else {
      strcpy(result, output.szMessage); // this should work but doesn't
    }

    FreeINCHI(&output);

    return status;
}

// see:
// https://stackoverflow.com/questions/31476632/
// https://stackoverflow.com/a/617606/54426
clock_t __wrap_clock()
{
    return 0;
}
