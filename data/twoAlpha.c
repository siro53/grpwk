#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define strNum 400001

int main(int argc, char **argv){
    assert(argc == 2);
    FILE *fp_ref = fopen(argv[1], "r");
    assert(fp_ref != NULL);

    int i,j;
    int c_after;
    int sets[4][4];
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            sets[i][j]=0;

    int c_before = getc(fp_ref);
    for(i=1;i<strNum;i++){
        c_after = getc(fp_ref);
        sets[c_before-'a'][c_after-'a']++;
        c_before = c_after;
    }

    FILE *fp_out = fopen("Two.txt", "w");
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            fprintf(fp_out, "%c%c: %d\n", 'a'+i, 'a'+j, sets[i][j]);
    
    fclose(fp_ref);
    fclose(fp_out);
    return 0;
}