#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "ahocorasick.h"

void aho_init(ahocorasick * restrict aho) {
    memset(aho, 0, sizeof(ahocorasick));
}

int aho_add_match_text(ahocorasick * restrict aho, string_s *text) {
    if (aho->text_id == AHO_SIZE) return FALSE;

    text->id = aho->text_id++;
    aho->list[text->id] = text;
    trie_add(&aho->trie, text, text->str);

    return TRUE;
}

int aho_add_similar_text(ahocorasick * restrict aho, const char * restrict data, const string_s * restrict original) {
    trie_add(&aho->trie, original, data);
    return TRUE;
}

string_s *aho_search_match_text(ahocorasick * restrict aho, const int id) {
    return aho->list[id];
}

void aho_create_trie(ahocorasick * restrict aho) {
    trie_init(&aho->trie);
}

void aho_connect_trie(ahocorasick * restrict aho) {
    trie_connect(&aho->trie);
}

int aho_search(ahocorasick * restrict aho, const char *data, int len) {
    int counter = 0;
    aho_node *current = &aho->trie.root;

    for (int i=0; i<len; i++) {
        string_s *result = trie_find(&current, data[i]);
        if (result == NULL) continue;

        aho_match_t match;
        match.id = result->id;
        match.len = result->len;
        match.pos = i - result->len + 1;

        counter++;
        // printf("substitute to %s from ", result->data);
        if (aho->callback_match) aho->callback_match(aho->callback_arg, &match);
    }

    return counter;
}

inline void aho_register_match_callback(ahocorasick * restrict aho, void (*callback_match)(void *arg, aho_match_t *), void *arg) {
    aho->callback_arg = arg;
    aho->callback_match = callback_match;
}
