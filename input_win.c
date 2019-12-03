#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "example/grpwk.h"

int main_prg(int, char **);

int main(int argc, char **argv)
{
    __clock_t c_start, c_end;

    c_start = clock();
    main_prg(argc, argv);
    c_end = clock();

    printf("%f\n", (double)(c_end - c_start) / CLOCKS_PER_SEC);
    return (0);
}

int main_prg(int argc, char **argv)
{
    assert(argc == 3);
    FILE *fp_in = fopen(argv[1], "r");
    assert(fp_in != NULL);
    FILE *fp_out = fopen(argv[2], "w");
    assert(fp_out != NULL);

    /*typedef struct
    {char str[120];
        int len;　//Prototype_Bigram.c}
    String_S;*/
    /*構造体*/

    String_S(t, s) = from_file();
    grpwk(const String_s t, const String_s s);

    //string_s とlengthの構造体 char str 120

    /**implement here
        *
   * read input values from fp_in
        * write output values to fp_out
        **/
    return 0;
}