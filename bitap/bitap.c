#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

//#include "../string_info.h"
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
    /*
    if (pattern_len > 31)
        return "The pattern is too long!";
  
    /* Initialize the bit array R */
    R = ~1UL;

    /* Initialize the pattern bitmasks */
    /*
    for (i = 0; i <= CHAR_MAX; ++i) {
        pattern_mask[i] = ~0ULL; // pattern masks = binary 1
    }
    */
    pattern_mask['a'] = ~0UL;
    pattern_mask['b'] = ~0UL;
    pattern_mask['c'] = ~0UL;
    pattern_mask['d'] = ~0UL;
    pattern_mask['\0'] = ~0UL;
    pattern_mask['x'] = 0UL;
    pattern_mask['z'] = ~0UL;

    //printf("%s\n", "=====pattern_mask of each char of the pattern=====");
    for (i = 0; i < pattern_len; ++i) {
        pattern_mask[pattern[i]] &= ~(1UL << i);
    }

    //printf("\n%s\n", "=====finding a match=====");
    for (i = 0; text[i] != '\0'; ++i) {

        /* Update the bit array */
        R |= pattern_mask[text[i]];
        R <<= 1UL;
 
        if (0 == (R & (1UL << pattern_len)))
            return (i - pattern_len) + 1;
    }
 
    return -1;
}

/** t: 虫食い, s: バラ, num: バラの数, startNum: バラの開始位置, out: 回答
 * 回答をreturn
 * バラが32文字以上だとバグる
 */
char* bitap(char* t, string_s* s, int num, int startNum, char* out){
    char sheet[T_LENGTH];
    strcpy(sheet, t);
    int i,j;
    int pos;

    for(i=startNum;i<num;i++){
        pos = bitap_bitwise_search(sheet, s[i].str);
        for(j=0;j<s[i].len;j++){
            out[pos+j] = s[i].str[j];
            sheet[pos+j] = 'z';
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