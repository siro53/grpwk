#pragma once

#include "string_info.h"
#include "linked_list.h"

#define MAX_NODE 4
#define FALSE 0
#define TRUE 1

typedef struct _node {
    int data;
    unsigned int ref_count;

    struct _node *parent, *child[MAX_NODE];

    int end;
    linked_list output_list;

    struct _node *failure_link, *output_link;
} aho_node;

typedef struct {
    aho_node root;
} aho_trie;

void trie_init(aho_trie * t);
void trie_destroy(aho_trie * t);

int trie_add(aho_trie * t, string_s * text, char * parent);
void trie_connect(aho_trie * t);
void trie_delete(aho_trie * t);
linked_list *trie_find(aho_node ** t, char text);

void trie_print(aho_trie * t);
