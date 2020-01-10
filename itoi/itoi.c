#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ahocorasick.h"
#include "grpwk.h"
#include "itoi.h"

int strsim(char *t, int convert, int length) {
    for (int i=0; i<length; i++) {
        if (t[i] == 'a' && (convert >> i & 1)) return 0;
        if (t[i] == 'x' && (convert >> i & 1) == 0) return 0;
    }
    return 1;
}

// outcome functions for testing
void callback_add2linked_list(ahocorasick * aho, linked_list *l, int pos) {
    printf("%d\n", l->length);
    linked_node *iter = l->top;
    for (int v=0; v<l->length; v++, iter = iter->next) {
        int text_len = aho->s[iter->data].len;
        int index = pos-text_len+1;

        if (!strsim(&aho->t[index], iter->place, text_len)) continue;

        // s_count[i].append(text.index)
        linked_push_int(&aho->s_count[iter->data], index, 1); // <- index of first letter

        // t_opt[i].append(i, place)
        for (int i=0; i<text_len; i++) {
            linked_push_node(&aho->t_opt[index + i], iter->data, i, 1);
        }
    }
}

// 入力されたintの中で何個のビットが立っているかを返す
int bitcount(int bits) {
    bits = (bits & 0x55555555) + (bits >> 1 & 0x55555555);
    bits = (bits & 0x33333333) + (bits >> 2 & 0x33333333);
    bits = (bits & 0x0f0f0f0f) + (bits >> 4 & 0x0f0f0f0f);
    bits = (bits & 0x00ff00ff) + (bits >> 8 & 0x00ff00ff);
    return (bits & 0x0000ffff) + (bits >> 16 & 0x0000ffff);
}

// bitchangeにおいて立っているビットの場所の文字を'a'に置換する
int convert(char *tmp, char *s, int length, int bitchange) {
    for (int i=0; i<length; i++) {
        // if (bitchange >> i & 1) {
        //     if (s[i] == 'a') return 0;
        //     else tmp[i] = 'a';
        // } else tmp[i] = s[i];
        tmp[i] = bitchange >> i & 1 ? 'a' : s[i];
    }
    tmp[length] = '\0';
    return 1;
}

// アホコラを使用したあいまい検索の関数
void ahocoralike(char *t, string_s s[], int from, int to, linked_list *t_opt, linked_list *s_count) {
    /* おまじない */
    ahocorasick aho;
    aho_init(&aho, t, s);
    aho_create_trie(&aho);
    aho_register_option_lists(&aho, t_opt, s_count);
    aho_register_match_callback(&aho, callback_add2linked_list);

    char tmp[120];

    for (int i=from; i<to; ++i) {
        aho_add_match_text(&aho, &s[i]); /* 木にキーを追加 */

        /* s[i]が虫食いされて生じうる文字列を木に追加 */
        double max_bit = s[i].len / 2; /* 虫食いされる個数は文字列長の半分以下に限定 */
        int until = (1<<s[i].len)-1; /* 文字列長分のビットを用意 */
        for (int j=1; j<=until; j++) {
            if (bitcount(j) < max_bit) { /* 文字列長の半分以下のビットが立っているなら */
                if (convert(tmp, s[i].str, s[i].len, j)) /* 文字列を虫食いしてtmpに保存 */
                    aho_add_similar_text(&aho, tmp, &s[i], j); /* トライ木に挿入 */
            }
        }
    }

    aho_connect_trie(&aho); /* トライ木を整理 */
    printf("connect done\n");
    aho_search(&aho, t, T_LENGTH);
    printf("search done\n");
    aho_destroy(&aho);
}

void s_opt_insert(linked_list *s_opt, int s_count, string_s *s_i) {
    if (s_count < S_OPT_LEN) {
        if (s_i->len >= BM_TO) linked_unshift_int(&s_opt[s_count], s_i->id, 0);
        else linked_push_int(&s_opt[s_count], s_i->id, 0);
    }
}

/* delete all other s that overlaps with the option */
void eliminate(int t_index, linked_list *t_opt, linked_list *s_opt, linked_list *s_count, string_s *s) {
    // eliminate other options within the substituted places
    while (t_opt[t_index].length != 0) {
        // the other option
        linked_node *other = linked_pop_node(&t_opt[t_index], 0);
        if (s_count[other->data].length == 0) { // same as the insert option
            free(other);
            continue;
        }

        // go to s_count[other.id] and delete the option to insert here
        if (linked_delete_int(&s_count[other->data], t_index - other->place)) {
            // reinsert the deleted option to s_opt
            s_opt_insert(s_opt, s_count[other->data].length, &s[other->data]);
        }
        free(other);
    }
}