#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp_in = fopen(argv[1], "r");
    assert(fp_in != NULL);
    FILE *fp_out = fopen(argv[2], "r");
    assert(fp_out != NULL);

    char in[500000], out[500000];
    fscanf(fp_in, "%s", in);
    fscanf(fp_out, "%s", out);

    int counter = 0, x = 0;
    for (int i=0; i<strlen(in); i++) {
        counter += (in[i] != out[i]);
        counter -= (in[i] == 'x') & (out[i] == 'a');
        x += in[i] == 'x';
    }
    counter += abs(strlen(in) - strlen(out));

    printf("edit distance: %d, strlen: %lu, ratio: %f%%, x: %d\n", counter, strlen(in), 100 - (double)counter / strlen(in) * 100, x);

    return 0;
}
