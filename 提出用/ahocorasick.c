#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ahocorasick.h"

// ahocorasick型の変数の初期化
void aho_init(ahocorasick * aho, string_s *s) {
    memset(aho, 0, sizeof(ahocorasick));
    aho->s = s;
}

void aho_destroy(ahocorasick * aho) {
    aho_clear_trie(aho);
}

/** キー(string_s *s_i)を木に追加
 * return 挿入成功：TRUE、容量を超過：FALSE
 */
int aho_add_match_text(ahocorasick * aho, string_s *text) {
    trie_add(&aho->trie, text, text->str);
    return TRUE;
}

/** 曖昧検索用文字列挿入用(木に挿入する文字列と探索成功時の返す文字列が違う場合に使用)
 * 木に挿入する文字列をメモリに保存せずに済む
 * data：曖昧の文字列、original：虫食い前のデータ
 */
int aho_add_similar_text(ahocorasick * aho, char * data, string_s * original) {
    trie_add(&aho->trie, original, data);
    return TRUE;
}

// トライ木を生成
void aho_create_trie(ahocorasick * aho) {
    trie_init(&aho->trie);
}

// トライ木からアホコラを作る
void aho_connect_trie(ahocorasick * aho) {
    trie_connect(&aho->trie);
}

void aho_clear_trie(ahocorasick * aho) {
    trie_destroy(&aho->trie);
}

/** 検索関数(data：t'、len：len(t'))
 * return マッチしたキーの数
 */
int aho_search(ahocorasick * aho, char *data, int len) {
    int counter = 0;
    aho_node *current = &aho->trie.root;

    for (int i=0; i<len; i++) {
        linked_list *result = trie_find(&current, data[i]);
        if (result == NULL) continue;
        counter++;
        // printf("substitute to %s from ", result->data);
        aho->callback_match(aho, result, i);
    }

    return counter;
}

// 探索が成功した際に実行される関数を設定する関数
inline void aho_register_match_callback(ahocorasick * aho, void (*callback_match)(ahocorasick * aho, linked_list* l, int pos)) {
    aho->callback_match = callback_match;
}

void aho_register_option_lists(ahocorasick * aho, linked_list *t_opt, linked_list *s_count) {
    aho->t_opt = t_opt;
    aho->s_count = s_count;
}
