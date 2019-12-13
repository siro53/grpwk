#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ahocorasick.h"

// ahocorasick型の変数の初期化
void aho_init(ahocorasick * restrict aho) {
    memset(aho, 0, sizeof(ahocorasick));
}

/** キー(string_s *s_i)を木に追加、引数のstring_s->idを変更
 * return 挿入成功：TRUE、容量を超過：FALSE
 */
int aho_add_match_text(ahocorasick * restrict aho, string_s *text) {
    if (aho->text_id == AHO_SIZE) return FALSE;

    text->id = aho->text_id++;
    aho->list[text->id] = text;
    trie_add(&aho->trie, text, text->str);
    // if (text->id % 1000 == 0) printf("%d (%d)\n", text->id, text->len);

    return TRUE;
}

/** 曖昧検索用文字列挿入用(木に挿入する文字列と探索成功時の返す文字列が違う場合に使用)
 * 木に挿入する文字列をメモリに保存せずに済む
 * data：曖昧の文字列、original：虫食い前のデータ
 */
int aho_add_similar_text(ahocorasick * restrict aho, char * restrict data, string_s * restrict original) {
    trie_add(&aho->trie, original, data);
    return TRUE;
}

// idに相当するstring_sを返す
string_s *aho_search_match_text(ahocorasick * restrict aho, int id) {
    return aho->list[id];
}

// トライ木を生成
void aho_create_trie(ahocorasick * restrict aho) {
    trie_init(&aho->trie);
}

// トライ木からアホコラを作る
void aho_connect_trie(ahocorasick * restrict aho) {
    trie_connect(&aho->trie);
}

/** 検索関数(data：t'、len：len(t'))
 * return マッチしたキーの数
 */
int aho_search(ahocorasick * restrict aho, char *data, int len) {
    int counter = 0;
    aho_node *current = &aho->trie.root;

    for (int i=0; i<len; i++) {
        string_s *result = trie_find(&current, data[i]);
        if (result == NULL) continue;

        aho_match_t match;
        match.id = result->id;
        match.len = result->len;
        match.pos = i - result->len + 1;
        match.s = result->str;

        counter++;
        // printf("substitute to %s from ", result->data);
        if (aho->callback_match) aho->callback_match(aho->callback_arg, &match);
    }

    return counter;
}

// 探索が成功した際に実行される関数を設定する関数
inline void aho_register_match_callback(ahocorasick * restrict aho, void (*callback_match)(void *arg, aho_match_t *), void *arg) {
    aho->callback_arg = arg;
    aho->callback_match = callback_match;
}
