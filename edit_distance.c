//参考にしました(sukeさん)
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define strNum 400001

int main(int argc, char **argv)
{
    assert(argc == 3);
    FILE *fp_in = fopen(argv[1], "r");
    assert(fp_in != NULL);
    FILE *fp_ref = fopen(argv[2], "r");
    assert(fp_ref != NULL);

    int i;
    int c_in, c_ref;
    int edit_distance = 0;

    for (i = 0; i < strNum; i++)
    {
        c_in = getc(fp_in);
        c_ref = getc(fp_ref);

        if (c_in != c_ref)
        {
            edit_distance += 1;
        }
    }

    fclose(fp_in);
    fclose(fp_ref);

    printf("edit_distance = %d\n", edit_distance);

    return 0;
}
