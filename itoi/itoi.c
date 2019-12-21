#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ahocorasick.h"
#include "itoi.h"

// outcome functions for testing
void callback_add2linked_list(ahocorasick * aho, linked_list *l, int pos) {
    linked_node *iter = l->top;
    for (int v=0; v<l->length; v++, iter = iter->next) {
        string_s *text = &aho->s[iter->data];

        // s_count[i].append(text.pos)
        linked_push_int(&aho->s_count[iter->data], pos-text->len+1, 1); // <- index of first letter

        // t_opt[i].append(i, place)
        for (int i=0; i<text->len; i++) {
            linked_push_node(&aho->t_opt[pos-text->len+1 + i], iter->data, i, 1);
        }
    }
}

// 入力されたintの中で何個のビットが立っているかを返す
int bitcount(unsigned long long bits) {
    bits = (bits & 0x5555555555555555) + (bits >> 1 & 0x5555555555555555);
    bits = (bits & 0x3333333333333333) + (bits >> 2 & 0x3333333333333333);
    bits = (bits & 0x0f0f0f0f0f0f0f0f) + (bits >> 4 & 0x0f0f0f0f0f0f0f0f);
    bits = (bits & 0x00ff00ff00ff00ff) + (bits >> 8 & 0x00ff00ff00ff00ff);
    bits = (bits & 0x0000ffff0000ffff) + (bits >> 16 & 0x0000ffff0000ffff);
    return (bits & 0x00000000ffffffff) + (bits >> 32 & 0x00000000ffffffff);
}

// bitchangeにおいて立っているビットの場所の文字を'a'に置換する
void convert(char *tmp, char *s, int len, unsigned long long bitchange) {
    for (int i=0; i<len; i++) {
        if (bitchange >> i & 1) tmp[i] = 'a';
        else tmp[i] = s[i];
    }
    tmp[len] = '\0';
}

// アホコラを使用したあいまい検索の関数
void ahocoralike(char *t, string_s s[], int from, int to, linked_list *t_opt, linked_list *s_count) {
    /* おまじない */
    ahocorasick aho;
    aho_init(&aho, s);
    aho_create_trie(&aho);
    aho_register_option_lists(&aho, t_opt, s_count);
    aho_register_match_callback(&aho, callback_add2linked_list);

    char tmp[120];

    for (int i=from; i<to; ++i) {
        aho_add_match_text(&aho, &s[i]); /* 木にキーを追加 */

        /* s[i]が虫食いされて生じうる文字列を木に追加 */
        int max_bit = s[i].len / 2; /* 虫食いされる個数は文字列長の半分以下に限定 */
        unsigned long long until = ((unsigned long long)1<<s[i].len)-1; /* 文字列長分のビットを用意 */
        for (unsigned long long j=1; j<=until; j++) {
            if (bitcount(j) < max_bit) { /* 文字列長の半分以下のビットが立っているなら */
                convert(tmp, s[i].str, s[i].len, j); /* 文字列を虫食いしてtmpに保存 */
                aho_add_similar_text(&aho, tmp, &s[i]); /* トライ木に挿入 */
            }
        }
    }

    aho_connect_trie(&aho); /* トライ木を整理 */
    aho_search(&aho, t, T_LENGTH);
    aho_destroy(&aho);

    /* TODO: test */
    // for (int i=from; i<to; i++) {
    //     if (s_count[s[i].id] > 100) printf("%d: %d, %s(%d)\n", s[i].id, s_count[s[i].id], s[i].str, s[i].len);
    // }
    // for (int i=0; i<T_LENGTH; i++) {
    //     if (t_opt[i].length < 3) {
    //         printf("%d: ", i);
    //         linked_print(&t_opt[i]);
    //     }
    // }
}

int s_opt_insert(linked_list *s_opt, int s_count, int index) {
    if (s_count < 100) {
        linked_push_int(&s_opt[s_count], index, 0);
        return 1;
    } else return 0;
}

/* delete all other s that overlaps with the option */
void discriminate(int s_id, int s_pos, string_s *text, linked_list *t_opt, linked_list *s_opt, linked_list *s_count) {
    linked_destroy(&s_count[s_id]);

    // discriminate other options within the substituted places
    for (int t_index=0; t_index<text->len; t_index++) {
        while (t_opt[t_index + s_pos].length != 0) {
            // the other option
            linked_node *other = linked_pop_node(&t_opt[t_index + s_pos], 0);
            if (other->data == s_id || s_count[other->data].length == 0) { // same as the insert option
                free(other);
                continue;
            }

            // go to s_count[other.id] and delete the option to insert here
            if (linked_delete_int(&s_count[other->data], t_index + s_pos - other->place)) {
                // reinsert the deleted option to s_opt
                s_opt_insert(s_opt, s_count[other->data].length, other->data);
            }
            free(other);
        }
    }
}