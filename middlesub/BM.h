#pragma once

#include "../string_info.h"
#include "../linked_list.h"

typedef struct Node *link;
struct Node{
    int *id;
    link b;
    int *x;
    int *count;
};

#define High(A, B) (A > B) ? A : B
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

void BM(string_out * t_in, string_s * s, int to, string_out *t_out, linked_list *s_count, linked_list *s_opt);
