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

size_t inchi_to_inchikey(char *inchi, char *result)
{
/* BH from mol2inchi.c */
    int xhash1=0;
    int xhash2=0;
    char szXtra1[256], szXtra2[256];
    int ik_ret = GetINCHIKeyFromINCHI(inchi, xhash1, xhash2, ikey, szXtra1, szXtra2);
    if (ik_ret!=0)
        ikey[0]='\0';
    strcpy(ikey, result);
    return ik_ret;
}

// see:
// https://stackoverflow.com/questions/31476632/
// https://stackoverflow.com/a/617606/54426
clock_t __wrap_clock()
{
    return 0;
}
