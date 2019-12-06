#pragma once

#include "string_info.h"

#define MAX_NODE 4
#define FALSE 0
#define TRUE 1

typedef struct _node {
    int data;
    unsigned int ref_count;

    struct _node *parent, *child[MAX_NODE];

    int end;
    string_s *output_text;

    struct _node *failure_link, *output_link;
} aho_node;

typedef struct {
    aho_node root;
} aho_trie;

void trie_init(aho_trie * restrict t);

int trie_add(aho_trie * restrict t, string_s * restrict text, char * restrict parent);
void trie_connect(aho_trie * restrict t);
void trie_delete(aho_trie * restrict t);
string_s *trie_find(aho_node ** restrict t, char text);

void trie_print(aho_trie * restrict t);
