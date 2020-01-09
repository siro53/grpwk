#pragma once

#include "ahotrie.h"
#include "string_info.h"
#include "linked_list.h"

#define AHO_SIZE 45000

typedef struct _ahocorasick {
    aho_trie trie;
    string_s *s;
    char *t;

    void (*callback_match)(struct _ahocorasick * aho, linked_list* l, int pos);
    linked_list *t_opt;
    linked_list *s_count;
} ahocorasick;

void aho_init(ahocorasick * aho, char *t, string_s *s);
void aho_destroy(ahocorasick * aho);

void aho_add_match_text(ahocorasick * aho, string_s *text);
void aho_add_similar_text(ahocorasick * aho, char * data, string_s * original, int convert);

void aho_create_trie(ahocorasick * aho);
void aho_connect_trie(ahocorasick * aho);
void aho_clear_trie(ahocorasick * aho);

void aho_search(ahocorasick * aho, char *text, int len);

void aho_register_match_callback(ahocorasick * aho, void (*callback_match)(ahocorasick * aho, linked_list* l, int pos));
void aho_register_option_lists(ahocorasick * aho, linked_list *t_opt, linked_list *s_count);
