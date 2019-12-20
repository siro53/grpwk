#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "string_info.h"
#include "constructions.h"

// change here to include your files!!
#include "example/grpwk.h"

int main_prg(int, char **);
void test_instant(void);

int main(int argc, char **argv)
{
    unsigned long int  c_start, c_end;


    c_start = clock();
    //main_prg(argc, argv);
    //printf("test");


    test_instant();
    c_end = clock();

    printf("%lf\n", (double)(c_end - c_start) / CLOCKS_PER_SEC);
    return (0);
}

int main_prg(int argc, char **argv)
{
    assert(argc == 3);
    FILE *fp_in = fopen(argv[1], "r");
    assert(fp_in != NULL);
    FILE *fp_out = fopen(argv[2], "w");
    assert(fp_out != NULL);

    string_s  *s = malloc(sizeof(string_s *) * 50000);
    char t[T_LENGTH + 1];

    // input t
    fscanf(fp_in, "%s", t);

    // input s[]
    int i = 0;
    while (~fscanf(fp_in, "%s", s[i].str)) s[i++].len = strlen(s[i].str);

    // sort s_i
    ConstructSMatrix(s,i);

    fprintf(fp_out, "%s\n", grpwk(t,s,i));


    return 0;
}
