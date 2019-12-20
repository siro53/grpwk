#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ahocorasick.h"
#include "ahocora.h"

// outcome functions for testing
void callback_substitute_zeros(void *arg, aho_match_t *m) {
    char *text = (char *)arg;

    // for (int i=m->pos; i<m->pos+m->len; i++) printf("%c", text[i]);
    // printf(" (match id: %d position: %d length: %d)\n", m->id, m->pos, m->len);

    /* もしarg(下で言うans)の該当部分が0だったときに文字を代入 */
    /* TODO: まだ正確なやり方を実装していないため、暫定的に */
    for (int i=0; i<m->len; i++) if (text[m->pos+i] == 'x') text[m->pos+i] = m->s[i];
}

void callback_count_options(void *arg, aho_match_t *m) {
    int *tmp = (int *)arg;
    tmp[m->id] += 1;
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
char *ahocoralike(char *t, string_s s[], int len) {
    /* おまじない */
    ahocorasick aho;
    aho_init(&aho);
    aho_create_trie(&aho);

    char tmp[120];

    for (int i=0; i<len; ++i) {
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
    // trie_print(&aho.trie);

    char *ans = (char *)calloc(T_LENGTH + 1, sizeof(char)); /* 変換後を保存する文字列 */
    strcpy(ans, t);
    aho_register_match_callback(&aho, callback_substitute_zeros, (void *)ans); /* 探索成功時に実行される関数を定義。関数は上を参照 */

    // int count[41000] = {0};
    // aho_register_match_callback(&aho, callback_count_options, (void *)count);

    // sprintf(ans, "total match: %d\n", aho_search(&aho, t, T_LENGTH));
    aho_search(&aho, t, T_LENGTH);

    // for (int i=0; i<len; i++) {
    //     printf("%d ", count[i]);
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
