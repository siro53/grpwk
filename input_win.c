#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
// #include <time.h>
#include "string_info.h"

// TODO: change here to include your files!!
#include "submit/grpwk.h"

int main_prg(int, char **);

int main(int argc, char **argv) {
    struct rusage u;
    getrusage(RUSAGE_SELF, &u);
    struct timeval start = u.ru_utime;

    // clock_t c_start = clock(), c_end;
    main_prg(argc, argv);

    struct timeval end = u.ru_utime;
    // c_end = clock();

    // printf("%f\n", (double)(c_end - c_start) / CLOCKS_PER_SEC);
    fprintf(stderr, "%lf\n", (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) * 1e-6);
    return 0;
}

int sort_f(const void *a, const void *b) {
    return ((string_s *)b)->len - ((string_s *)a)->len;
}

int main_prg(int argc, char **argv) {
    assert(argc == 3);
    FILE *fp_in = fopen(argv[1], "r");
    assert(fp_in != NULL);
    FILE *fp_out = fopen(argv[2], "w");
    assert(fp_out != NULL);

    char t[T_LENGTH];
    string_s s[45000];

    // input t
    fscanf(fp_in, "%s", t);

    // input s[]
    int counter = 0;
    for (; fscanf(fp_in, "%s", s[counter].str) != EOF; ++counter) s[counter].len = strlen(s[counter].str);
    qsort(s, counter, sizeof(string_s), sort_f);

    for (int i=0; i<counter; i++) s[i].id = i;

    fprintf(fp_out, "%s\n", grpwk(t, s, counter));

    return 0;
}
