#pragma once

#include "ahotrie.h"
#include "ahotext.h"

typedef {
    int id, pos, len;
} aho_match;

typedef {
    int text_id;
    aho_text *head, *tail;
    int text_count;

    aho_trie trie;

    void (*callback_match)(void *arg, aho_match *m);
    void *callback_arg;
} ahocorasick;

void aho_init(ahocorasick * restrict aho);
void aho_destroy(ahocorasick * restrict aho);

int aho_add_match_text(ahocorasick * restrict aho, const char* text, unsigned int len);
bool aho_del_match_text(ahocorasick * restrict aho, const int id);
void aho_clear_match_text(ahocorasick * restrict aho);

void aho_create_trie(ahocorasick * restrict aho);
void aho_clear_trie(ahocorasick * restrict aho);

unsigned int aho_search(ahocorasick * restrict aho, const char *text, int len);

void aho_register_match_callback(ahocorasick * restrict aho, void (*callback_match)(void* arg, aho_match_t*), void *arg);

void aho_print_match_text(ahocorasick * restrict aho);
