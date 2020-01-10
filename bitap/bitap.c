#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#include "bitap.h"

//#define T_LEN 17

/* the bitap algorithm */
int bitap_bitwise_search(const char *text, const char *pattern)
{
    int pattern_len = strlen(pattern);
    unsigned long R;
    unsigned long pattern_mask[CHAR_MAX+1];
    int i;
 
    if (pattern[0] == '\0')
        return 0;

    /* Initialize the bit array R */
    R = ~1UL;

    /* Initialize the pattern bitmasks */
    
    pattern_mask['a'] = ~0UL;
    pattern_mask['b'] = ~0UL;
    pattern_mask['c'] = ~0UL;
    pattern_mask['d'] = ~0UL;
    pattern_mask['\0'] = ~0UL;
    pattern_mask['x'] = 0UL;
    pattern_mask['z'] = ~0UL;

    for (i = 0; i < pattern_len; ++i) {
        pattern_mask[pattern[i]] &= ~(1UL << i);
    }

    for (i = 0; text[i] != '\0'; ++i) {

        /* Update the bit array */
        R |= pattern_mask[text[i]];
        R <<= 1UL;
 
        if (0 == (R & (1UL << pattern_len)))
            return (i - pattern_len) + 1;
    }
 
    return -1;
}

/** t: 虫食い, s: バラ, num: バラの数, startNum: バラの開始位置, out: 回答, check: 埋めたかのチェック
 * 回答をreturnする
 * バラが32文字以上だとバグる
 * t_outの使い方が違うかもしれない
 */
char* bitap(char* t, string_s* s, int num, int startNum, char* out, string_out* t_out){
    int i,j;
    int pos;

    char check[T_LENGTH+1];

    for(i=0;i<T_LENGTH;i++){
        if(t_out->str[i]!='x') check[i]='z';
        else check[i] = t[i];
    }
    check[T_LENGTH] = '\0';


    for(i=startNum;i<num;i++){
        if(s[i].len==1) break;
        pos = bitap_bitwise_search(check, s[i].str);
        for(j=0;j<s[i].len;j++){
            out[pos+j] = s[i].str[j];
            check[pos+j] = 'z';
        }
    }


    for(i=0;i<T_LENGTH;i++){
        if(out[i]=='x') out[i] = 'a';
    }

    return out;
}

/*
int main(int argc, char const *argv[])
{
    char pattern[120], txt[400001];
    printf("%s\n", "enter: text pattern ");
    scanf("%s %s", txt, pattern);

    printf("%d\n", bitap_bitwise_search(txt, pattern));
    //printf("%d\n", bitap_yade(txt, pattern));

    string_s str[2] = {{"abdba", 5, 1}, {"dcabad", 6, 2}};
    
    char* input = "dcaxaddcabxbaadc";

    char *output = (char *)malloc(17 * sizeof(char));
    strcpy(output, input);

    printf("%s\n", output);
    output = bitap(input, str, 2, 0, output);
    printf("%s\n", output);
    return 0;
}
*/

/*
int sort_f(const void *a, const void *b) {
    return ((string_s *)b)->len - ((string_s *)a)->len;
}

int main(int argc, char **argv) {
    printf("start");
    assert(argc == 3);
    FILE *fp_in = fopen(argv[1], "r");
    assert(fp_in != NULL);
    FILE *fp_out = fopen(argv[2], "w");
    assert(fp_out != NULL);

    char t[T_LENGTH];
    string_s s[45000];

    // input t
    fscanf(fp_in, "%s", t);
    // for (int i=0; i<T_LENGTH; i++) if (t[i] == 'x') t[i] = 'a';

    // input s[]
    int counter = 0;
    for (; fscanf(fp_in, "%s", s[counter].str) != EOF; ++counter) s[counter].len = strlen(s[counter].str);
    qsort(s, counter, sizeof(string_s), sort_f);

    for (int i=0; i<counter; i++) s[i].id = i;

    char out[T_LENGTH+1];
    strcpy(out, t);

    fprintf(fp_out, "%s\n", bitap(t, s, counter, 0, out));

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
*/