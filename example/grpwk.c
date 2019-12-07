#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../constructions.h"
#include "grpwk.h"

char t_out[T_LENGTH + 1];

char *grpwk(char* t, string_s * s, int len) {

    printf("Start restoring text\n");
    string_out t_out_base, *t_out;
    t_out = &t_out_base; 
    ConstructTout(t_out,t);


    BM_entrance(t, s, len, len, t_out);

    return t_out.str;
}

void writeTout(char* t_temp){
    printf("Text restoration completed\n");
    strcpy(t_out, t_temp);
    printf("Copy text to t_out\n");
}