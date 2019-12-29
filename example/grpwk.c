#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../constructions.h"
#include "grpwk.h"
#include "BM.h"

char *grpwk(char *t, string_s *s, int len)
{

    string_out t_out_base, *t_out, t_in_base, *t_in;
    t_out = &t_out_base;
    t_in = &t_in_base;
    ConstructSMatrix(s, len);
    ConstructTout(t_out, t);
    ConstructTin(t_in, t);

    linked_list *t_opt = (linked_list *)malloc(sizeof(linked_list) * T_LENGTH);
    for (int i = 0; i < T_LENGTH; i++)
        linked_init(&t_opt[i]);
    int s_count_tmp[len];
    memset(s_count_tmp, 0, sizeof(int) * len);
    linked_list s_count[len];
    memset(s_count, 0, sizeof(linked_list) * len);

    BM_entrance(t_in, s, len, 0, t_out, s_count, t_opt);

    return t_out->str;
}
