#pragma once

#include "ahotrie.h"
#include "string_info.h"

#define AHO_SIZE 45000

typedef struct  {
    int id, pos, len;
    char *s;
    string_s *text;
} aho_match_t;

typedef struct {
    aho_trie trie;

    void (*callback_match)(void *arg, aho_match_t *m);
    void *callback_arg;
} ahocorasick;

void aho_init(ahocorasick * restrict aho);
void aho_destroy(ahocorasick * restrict aho);

int aho_add_match_text(ahocorasick * restrict aho, string_s *text);
int aho_add_similar_text(ahocorasick * restrict aho, char * restrict data, string_s * restrict original);

void aho_create_trie(ahocorasick * restrict aho);
void aho_connect_trie(ahocorasick * restrict aho);
void aho_clear_trie(ahocorasick * restrict aho);

int aho_search(ahocorasick * restrict aho, char *text, int len);

void aho_register_match_callback(ahocorasick * restrict aho, void (*callback_match)(void* arg, aho_match_t* m), void *arg);
