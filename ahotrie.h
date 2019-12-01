#pragma once

#define MAX_NODE 5

typedef struct _node {
    int data;
    unsigned int ref_count;

    struct _node *parent, *child[MAX_NODE];

    aho_text *output_text;

    struct _node *failure_link, *output_link;
} aho_node;

typedef struct {
    aho_node root;
} aho_trie;

void trie_init(aho_trie * restrict t);
void trie_destroy(aho_trie * restrict t);

int trie_add(aho_trie * restrict t, aho_text * restrict text);
void trie_connect(aho_trie * restrict t);
void trie_delete(aho_trie * restrict t);
aho_text *trie_find(aho_trie ** restrict t, const unsigned char text);

void trie_print(aho_trie * restrict t);
