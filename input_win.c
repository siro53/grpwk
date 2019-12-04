#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "string_s.h"

// change here to include your files!!
#include "itoi/grpwk.h"

int main_prg(int, char **);

int main(int argc, char **argv)
{
    clock_t c_start, c_end;

    c_start = clock();
    main_prg(argc, argv);
    c_end = clock();

    printf("%f\n", (double)(c_end - c_start) / CLOCKS_PER_SEC);
    return 0;
}

int main_prg(int argc, char **argv)
{
    assert(argc == 3);
    FILE *fp_in = fopen(argv[1], "r");
    assert(fp_in != NULL);
    FILE *fp_out = fopen(argv[2], "w");
    assert(fp_out != NULL);

    string_s t, s[50000];

    // input t
    fscanf(fp_in, "%s", t.str);
    t.len = strlen(t.str);

    // input s[]
    int counter = 0;
    for (; fscanf(fp_in, "%s", s[counter].str) != EOF; ++counter) s[counter].len = strlen(s[counter].str);

    fprintf(fp_out, "%s\n", grpwk(t, s, counter));

    return 0;
}
