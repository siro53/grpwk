#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ahotrie.h"
#include "queue.h"

// 新しいノードを生成
aho_node *node_init(int data, aho_node * restrict parent) {
    aho_node *node = (aho_node *)malloc(sizeof(aho_node));
    memset(node, 0, sizeof(aho_node));
    node->data = data;
    node->parent = parent;
    node->ref_count = 1;
    node->end = FALSE;
    return node;
}

// トライ木を初期化
void trie_init(aho_trie * restrict t) {
    if (t == NULL) t = (aho_trie *)malloc(sizeof(aho_trie));
    memset(t, 0, sizeof(aho_trie));
    t->root = *node_init(-1, NULL);
}

/** トライ木に文字列を挿入
 * string_s *text: ゴール
 * char *similar: 入力文字列
 * - aho_add_match_textのときは text->str == similar
 **/
int trie_add(aho_trie * restrict t, string_s * restrict text, char * restrict similar) {
    aho_node *current = &t->root;

    for (int i=0; i<text->len; i++) {
        int char_id = similar[i] - 'a';
        if (char_id > 3 || char_id < 0) return FALSE;

        if (current->child[char_id] == NULL) current->child[char_id] = node_init(char_id, current);
        else current->child[char_id]->ref_count++;

        current = current->child[char_id];
    }

    current->end = TRUE;
    current->output_text = text;

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

            if (tmp->child[i]->end) q->output_link = tmp->child[i];
            else q->output_link = tmp->child[i]->output_link;

            return TRUE;
        }
    }
    return FALSE;
}

// トライ木をアホコラに合わせて再構成
void trie_connect(aho_trie * restrict t) {
    queue que;
    que_init(&que);
    que_push(&que, &t->root);

    while (TRUE) {
        aho_node *node = que_pop(&que);
        if (node == NULL) break;

        for (int i=0; i<MAX_NODE; i++) {
            if (node->child[i] == NULL) continue;

            que_push(&que, node->child[i]);

            aho_node *tmp = node, *child = node->child[i];
            while (connect_link(tmp, child) == FALSE) tmp = tmp->failure_link;
        }
    }

    que_destroy(&que);
}

void trie_delete(aho_trie * restrict t) {
    queue que;
    que_init(&que);
    que_push(&que, &t->root);

    while (TRUE) {
        QUE_TYPE node = que_pop(&que);
        if (node == NULL) break;

        for (int i=0; i<MAX_NODE; i++) if (node->child[i] != NULL) que_push(&que, node->child[i]);

        if (node->parent == NULL) continue;
    }

    que_destroy(&que);
}

int find_node(aho_node ** restrict node, char text) {
    if (*node == NULL) return FALSE;

    if ((*node)->child[text] != NULL && text <= 3 && text >= 0) {
        *node = (*node)->child[text];
        return TRUE;
    }

    return FALSE;
}

// textが木に含まれる場合、終端に設定したstring_sを返す。含まれない場合はNULL。
string_s *trie_find(aho_node ** restrict node, char text) {
    while (find_node(node, text - 'a') == FALSE) {
        if (node == NULL || (*node)->parent == NULL) return NULL;
        *node = (*node)->failure_link;
    }

    if ((*node)->end) return (*node)->output_text;
    else if ((*node)->output_link) return (*node)->output_link->output_text;
    else return NULL;
}

// トライ木を表示。ノードが多くなってくると使い物にならない。
void trie_print(aho_trie * restrict t) {
    queue que;
    que_init(&que);
    que_push(&que, &t->root);

    while (TRUE) {
        QUE_TYPE node = que_pop(&que);
        if (node == NULL) break;

        for (int i=0; i<MAX_NODE; i++) if (node->child[i] != NULL) que_push(&que, node->child[i]);

        printf("%c, refs:%d, fail: %p, output:%p\n", node->data + 'a', node->ref_count, node->failure_link, node->output_link);
    }

    que_destroy(&que);
}
