#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string_info.h"
#include "ahocorasick.h"

int test_trie(void) {
    char *s[] = {
        "ab",
        "abc",
        "aaaaabddbdaaacccaacbaabacbaadb",
        "aaacdbdbcbcdbdbadaacbaadbdbdaacaaaaaadacababdadddacaacbaaaabdacdadadbabbbddaaddaaaaa",
        "abacbadaadbcaaabaaacbbaabadbababdbcadbd",
        "dbbbdaabaaabaabab",
        "daaadaaa",
        "dbaac",
        "ad",
        "bdadaabbaaadaabdd",
        "ddaabdd",
        "bdbabb",
        "abdb",
        "adbab",
        "aaabaaabcadba",
    };
    string_s text[100];

    aho_trie t;
    trie_init(&t); /* トライ木を初期化 */

    for (int i=0; i<15; i++) {
        strcpy(text[i].str, s[i]);
        text[i].len = strlen(s[i]);
        if (!trie_add(&t, &text[i], s[i])) /* トライ木にキーを挿入 */
            printf("error (unexpected input [^a-d]\n");
        printf("here\n");
    }
    trie_connect(&t); /* 再構成 */

    trie_print(&t);

    return 0;
}

// 検索成功時に実行される関数(あらかじめahoにセットしておく)
void callback_match_pos(void *arg, aho_match_t *m) {
    char *text = (char *)arg;

    printf("match text: ");
    for (int i=m->pos; i<m->pos+m->len; i++) printf("%c", text[i]);

    printf(" (match id: %d position: %d length: %d)\n", m->id, m->pos, m->len);
}

// char *sからそれに相当するstring_sを生成
string_s *new(char *s) {
    string_s *n = (string_s *)malloc(sizeof(string_s));
    n->len = strlen(s);
    strcpy(n->str, s);
    return n;
}

int test_ahocora(void) {
    ahocorasick aho;
    aho_init(&aho); /* aho初期化 */
    aho_create_trie(&aho); /* トライ木初期化 */
    /* 上二つの関数は必ず実行！！ */

    /* キーを木に追加 */
    aho_add_match_text(&aho, new("ab"));
    aho_add_match_text(&aho, new("abc"));
    aho_add_match_text(&aho, new("ca"));

    /* アホコラ用にトライ木を再構成 */
    aho_connect_trie(&aho);

    char test[] = "abcabcabcab";
    /* 探索成功時に実行される関数をセットする */
    aho_register_match_callback(&aho, callback_match_pos, (void *)test);

    trie_print(&aho.trie);

    printf("try: %s\n", test);
    printf("total match: %d\n", aho_search(&aho, test, strlen(test)));

    return 0;
}

int test_input(void) {
    ahocorasick aho;
    aho_init(&aho);
    aho_create_trie(&aho);

    char s[500000];
    FILE *fp = fopen("data/dat0_in", "r");
    fscanf(fp, "%s", s);
    // while (~fscanf(fp, "%s", s))
    //     if (strlen(s) >= 50)
    //         aho_add_match_text(&aho, s, strlen(s));

    fp = fopen("data/dat0_ref", "r");
    fscanf(fp, "%s", s);

    aho_connect_trie(&aho);
    aho_register_match_callback(&aho, callback_match_pos, (void *)s);

    printf("total match: %d\n", aho_search(&aho, s, strlen(s)));

    return 0;
}

int main(void) {
    // test_trie();
    // test_ahocora();
    // test_input();

    return 0;
}
