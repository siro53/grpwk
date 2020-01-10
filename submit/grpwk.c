#include <stdlib.h>
#include <string.h>

#include "../linked_list.h"
#include "grpwk.h"
#include "itoi.h"
#include "sunday.h"

// input_win.cから呼び出されるやつ
char *grpwk(char *t, string_s *s, int len)
{
    /* 文字数の区切りを決定 */
    int bm_until, aho_until;
    for (bm_until = 0; bm_until < len; ++bm_until)
        if (s[bm_until].len <= BM_TO)
            break;
    for (aho_until = bm_until; aho_until < len; aho_until++)
        if (s[aho_until].len <= AHO_TO)
            break;

    /* BMはじめ */
    string_out *t_out = (string_out *)malloc(sizeof(string_out));

    // output str init
    for (int i = 0; i < T_LENGTH; i++) t_out->str[i] = 'x';
    t_out->str[T_LENGTH] = '\0';

    // init option lists
    linked_list *t_opt = (linked_list *)malloc(sizeof(linked_list) * T_LENGTH);
    for (int i = 0; i < T_LENGTH; i++) linked_init(&t_opt[i]);
    linked_list s_count[len];
    memset(s_count, 0, sizeof(linked_list) * len);

    sunday(t, s, bm_until, t_opt, s_count);

    linked_list s_opt[S_OPT_LEN];
    memset(s_opt, 0, sizeof(linked_list) * S_OPT_LEN);

    // s_opt init
    for (int i = 50; i < aho_until; i++) {
        s_opt_insert(s_opt, s_count[i].length, &s[i]);
    }

    /* delete options where t is already determined by BM */
    for (int i = 0; i < T_LENGTH; i++) {
        if (t_out->str[i] != 'x') {
            eliminate(i, t_opt, s_opt, s_count, s);
        }
    }

    for (;;) {
        // get next s to insert into ans
        int s_id = -1;
        if (s_opt[1].length != 0) s_id = linked_pop_int(&s_opt[1], 0);
        else {
            for (int i = 2; i < S_OPT_LEN; i++) {
                if (s_opt[i].length != 0) {
                    s_id = linked_pop_int(&s_opt[i], 0);
                    break;
                }
            }
        }
        if (s_id == -1) break; // no option found
        if (s_count[s_id].length == 0) continue; // option already taken


        // option's text and place: index of first letter within t
        int s_pos = linked_pop_int(&s_count[s_id], 0);
        linked_init(&s_count[s_id]);
        // s_count[s_id].length = 0;

        /* delete other options */
        string_s *text = &s[s_id];

        for (int i = 0; i < text->len; i++) {
            t_out->str[s_pos + i] = text->str[i];
            eliminate(s_pos + i, t_opt, s_opt, s_count, s);
        }
    }

    for (int i = 0; i < T_LENGTH; i++) {
        if (t_out->str[i] != 'x') {
            t[i] = t_out->str[i];
        }
    }

    return t;
}
