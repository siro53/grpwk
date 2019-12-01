#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define strNum 400001

int main(int argc, char **argv){
    assert(argc == 3);
    FILE *fp_in = fopen(argv[1], "r");
    assert(fp_in != NULL);
    FILE *fp_ref = fopen(argv[2], "r");
    assert(fp_ref != NULL);

    int i;
    int c_in, c_ref;
    int alphas[4] = {0,0,0,0};
    int alphas_x[4] = {0,0,0,0};

    for(i=0;i<strNum;i++){
        c_in = getc(fp_in);
        c_ref = getc(fp_ref);
        if(c_ref=='a'||c_ref=='b'||c_ref=='c'||c_ref=='d') alphas[c_ref-'a']++;
        if(c_in != c_ref){
            if(c_in == 'x') alphas_x[c_ref-'a']++;
        }
    }

    FILE *fp_out = fopen("ABCD.txt", "w");
    for(i=0;i<4;i++)
        fprintf(fp_out, "%c 's num: %d\n", 'a'+i, alphas[i]);
    for(i=0;i<4;i++)
        fprintf(fp_out, "%c in x: %d\n", 'a'+i, alphas_x[i]);
    
    fclose(fp_in);
    fclose(fp_ref);
    fclose(fp_out);
    return 0;
}