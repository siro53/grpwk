#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ahocorasick.h"
#include "ahocora.h"

// outcome functions for testing
void callback_add2linked_list(ahocorasick * aho, linked_list *l, int pos) {
    linked_node *iter = l->top;
    for (int v=0; v<l->length; v++, iter = iter->next) {
        // s_count[i]++
        aho->s_count[iter->data]++;

        string_s text = aho->s[iter->data];
        // t_opt[i].append(i, place)
        for (int i=0; i<text.len; i++) {
            linked_push_node(&aho->t_opt[pos-text.len+1 + i], iter->data, i);
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
char *ahocoralike(char *t, string_s s[], int from, int to, linked_list *t_opt, int *s_count) {
    /* おまじない */
    ahocorasick aho;
    aho_init(&aho, s);
    aho_create_trie(&aho);

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

    char *ans = (char *)calloc(T_LENGTH + 1, sizeof(char));
    for (int i=0; i<strlen(t); i++) {
        ans[i] = t[i] != 'x' ? t[i] : 'a';
    }

    aho_register_option_lists(&aho, t_opt, s_count);
    aho_register_match_callback(&aho, callback_add2linked_list);

    aho_search(&aho, ans, T_LENGTH);
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

    int counter = 0;
    for (int i=0; i<T_LENGTH; i++) {
        if (ans[i] == 0) { /* わからない部分 */
            counter++;
            ans[i] = 'x';
            /* 本番はaを入れるが、今はわかったところとわからなかったところを明示的に区別するためにxを代入。詳細はtest_distance.cを参照 */
        }
    }
    printf("unknown places: %d\n", counter);

    return ans;
}
