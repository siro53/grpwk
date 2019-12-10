#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp_in = fopen("../data/dat0_ref", "r");
    assert(fp_in != NULL);
    FILE *fp_out = fopen("dat0_out.txt", "r");
    assert(fp_out != NULL);

    char in[500000], out[500000];
    fscanf(fp_in, "%s", in);
    fscanf(fp_out, "%s", out);

    int counter = 0;
    for (int i = 0; i < strlen(in); i++)
        counter += (in[i] != out[i]);
    counter += abs(strlen(in) - strlen(out));

    printf("edit distance: %d\n", counter);

    return 0;
}