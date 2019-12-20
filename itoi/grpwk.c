#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grpwk.h"
#include "ahocora.h"
#include "../linked_list.h"

// input_win.cから呼び出されるやつ
char *grpwk(char *t, string_s s[], int len) {
    int from, to;
    for (from = 0; from<len; ++from) if (s[from].len == AHO_FROM) break;
    for (to = from; to<len; to++) if (s[to].len == AHO_TO) break;

    linked_list *t_opt = (linked_list *)malloc(sizeof(linked_list) * T_LENGTH);
    for (int i=0; i<T_LENGTH; i++) linked_init(&t_opt[i]);
    int s_count[len];
    memset(s_count, 0, sizeof(int) * len);

    char *ans = ahocoralike(t, s, from, to, t_opt, s_count);
    return ans;
}
