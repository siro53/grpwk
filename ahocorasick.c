#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "ahocorasick.h"

void aho_init(ahocorasick * restrict aho) {
    memset(aho, 0, sizeof(ahocorasick));
}

void aho_destroy(ahocorasick * restrict aho) {
    aho_clear_match_text(aho);
    aho_clear_trie(aho);
}

int aho_add_match_text(ahocorasick * restrict aho, const char *data, int len) {
    if (aho->text_id == INT_MAX) return -1;

    aho_text *text = text_init(aho->text_id++, data, len);
    if (text == NULL || text->data == NULL) return -1;

    if (aho->head == NULL) {
        aho->head = text;
        aho->tail = text;
        aho->text_count++;
        return text->id;
    }

    aho->tail->next = text;
    text->prev = aho->tail;
    aho->tail = text;
    aho->text_count++;
    return text->id;
}

int aho_del_match_text(ahocorasick * restrict aho, const int id) {
    for (aho_text *iter = aho->head; iter != NULL; iter = iter->next) {
        if (iter->id == id) {
            if (iter == aho->head) {
                aho->head = iter->next;
                free(iter->data);
            } else if (iter == aho->tail) {
                aho->tail = iter->prev;
                free(iter->data);
            } else {
                iter->prev->next = iter->next;
                iter->next->prev = iter->prev;
                free(iter->data);
            }
            free(iter);
            aho->text_count--;
            return TRUE;
        }
    }
    return FALSE;
}

void aho_clear_match_text(ahocorasick * restrict aho) {
    for (int i=0; i<aho->text_id; i++) aho_del_match_text(aho, i);

    aho->text_id = 0;
}

void aho_create_trie(ahocorasick * restrict aho) {
    trie_init(&aho->trie);

    for (aho_text *iter = aho->head; iter != NULL; iter = iter->next) trie_add(&aho->trie, iter);
    trie_connect(&aho->trie);

    trie_print(&aho->trie);
}

void aho_clear_trie(ahocorasick * restrict aho) {
    trie_destroy(&aho->trie);
}

int aho_search(ahocorasick * restrict aho, const char *data, int len) {
    int counter = 0;
    aho_node *current = &aho->trie.root;

    for (int i=0; i<len; i++) {
        aho_match match;
        aho_text *result = trie_find(&current, data[i]);
        if (result == NULL) continue;

        match.id = result->id;
        match.len = result->len;
        match.pos = i - result->len + 1;

        counter++;
        if (aho->callback_match) aho->callback_match(aho->callback_arg, &match);
    }

    return counter;
}

inline void aho_register_match_callback(ahocorasick * restrict aho, void (*callback_match)(void *arg, aho_match *), void *arg) {
    aho->callback_arg = arg;
    aho->callback_match = callback_match;
}

void aho_print_match_text(ahocorasick * restrict aho) {
    for (aho_text *iter = aho->head; iter != NULL; iter = iter->next) {
        printf("id: %d, text:%s, len:%d\n", iter->id, iter->data, iter->len);
    }
}