#include <string.h>
#include <time.h>
#include "inchi_api.h"

int molfile_to_inchi(char *molfile, char *options, char *result)
{
    inchi_Output output;

    memset((void *)&output, 0, sizeof(output));
    MakeINCHIFromMolfileText(molfile, options, &output);

    int status = output.szInChI ? 0 : -1;

    strcpy(result, status == 0 ? output.szInChI : output.szLog);
    FreeINCHI(&output);

    return status;
}

size_t inchi_to_inchikey(char *inchi, char *result)
{
    int xhash1 = 0;
    int xhash2 = 0;
    char szXtra1[256], szXtra2[256], ikey[256];
    int ik_ret = GetINCHIKeyFromINCHI(inchi, xhash1, xhash2, ikey, szXtra1, szXtra2);

    if (ik_ret != 0) {
        ikey[0]='\0';
    }

    strcpy(result, ikey);

    return ik_ret;
}

// see:
// https://stackoverflow.com/questions/31476632/
// https://stackoverflow.com/a/617606/54426
clock_t __wrap_clock()
{
    return 0;
}