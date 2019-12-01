#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ahotrie.h"
#include "ahotext.h"
#include "queue.h"

#define FALSE 0
#define TRUE 1

aho_node *node_init(int data, aho_node * restrict parent) {
    aho_node *node = (aho_node *)malloc(sizeof(aho_node));
    memset(node, 0, sizeof(aho_node));
    node->data = data;
    node->parent = parent;
    node->ref_count = 1;
    return node;
}

void trie_init(aho_trie * restrict t) {
    memset(t, 0, sizeof(aho_trie));
    init(&(t->root));
}

void trie_destroy(aho_trie * restrict t) {
    trie_delete(t);
}

int trie_add(aho_trie * restrict t, aho_text * restrict text) {
    aho_node *current = &(t->root);

    for (int i=0; i<text->len-1; i++) {
        int char_id = text->data[i] - 'a';
        if (char_id > 3 || char_id < 0) break;

        if (current->child[char_id] == NULL) current->child[char_id] = node_init(char_id, current);
        else current->child[char_id]->ref_count++;

        current = current->child[char_id];
    }

    current->child[4] = node_init(4, current);
    current->child[4]->output_text = text;

    return TRUE;
}

int connect_link(aho_node *p, aho_node *q) {
    if (p->failure_link == NULL || p->parent == NULL) {
        q->failure_link = p;
        return TRUE;
    }

    aho_node *tmp = p->failure_link;
    for (int i=0; i<MAX_NODE; i++) {
        if (tmp->child[i] == NULL) continue;

        if (tmp->child[i]->data == q->data) {
            q->failure_link = tmp->child[i];

            if (tmp->child[i]->data == 4) q->output_link = tmp->child[i];
            else q->output_link = tmp->child[i]->output_link;

            return TRUE;
        }
    }
    return FALSE;
}

void trie_connect(aho_trie * restrict t) {
    queue *que;
    que_init(que, &(t->root));

    while (TRUE) {
        QUE_TYPE node = que_pop(que);
        if (node == NULL) break;

        for (int i=0; i<MAX_NODE; i++) {
            if (node->child[i] == NULL) continue;

            aho_node *tmp = node, *child = node->child[i];
            que_push(que, child);

            while (connect_link(tmp, child) == FALSE) tmp = tmp->failure_link;
        }

        free(node);
    }

    // que_destroy(que);
}

void trie_delete(aho_trie * restrict t) {
    queue *que;
    que_init(que, &(t->root));

    while (TRUE) {
        QUE_TYPE node = que_pop(que);
        if (node == NULL) break;

        for (int i=0; i<MAX_NODE; i++) if (node->child[i] != NULL) que_push(que, node->child[i]);

        if (node->parent == NULL) continue;

        free(node);
    }
}

int find_node(aho_node ** restrict node, const unsigned char text) {
    if (*node == NULL) return FALSE;

    if (text == '\0') {
        *node = (*node)->child[4];
        return TRUE;
    }
    if ((*node)->child[text - 'a'] != NULL) {
        *node = (*node)->child[text - 'a'];
        return TRUE;
    }

    return FALSE;
}

aho_text *trie_find(aho_trie ** restrict t, const unsigned char text) {
    while (find_node(t, text) == FALSE) {
        if (t == NULL || (*t)->parent == NULL) return NULL;
        *t = (*t)->failure_link;
    }

    if ((*t)->data == 4) return (*t)->output_text;
    if ((*t)->output_link) return (*t)->output_link->output_text;

    return NULL;
}

void trie_print(aho_trie * restrict t) {
    queue *que;
    que_init(que, &(t->root));

    while (TRUE) {
        QUE_TYPE node = que_pop(que);
        if (node == NULL) break;

        for (int i=0; i<MAX_NODE; i++) if (node->child[i] != NULL) que_push(que, node->child[i]);

        printf("%c, refs:%d, fail: %p, output:%p\n", node->data + 'a', node->ref_count, node->failure_link, node->output_link);
    }

    // que_destroy(que);
}
