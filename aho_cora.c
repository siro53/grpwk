#include <stdio.h>
#include <stdlib.h>
#include "aho_cora.h"

#define bitsword 17
#define digit(A, B) (((A) >> (bitsword-(B)-1)) & 1)

static aho *head, *z;

aho *NEW(AHO_TYPE data, aho *l, aho *r, int N) {
    aho *x = (aho *)malloc(sizeof(aho));
    x->data = data;
    x->l = l; x->r = r; x->N = N;
    return x;
}

void aho_init(void) {
    head = (z = NEW(aho_nulldata, NULL, NULL, 0));
}

void show_data(aho *h, void (*print_func)(AHO_TYPE)) {
    if (h == z) return;
    show_data(h->l, print_func);
    print_func(h->data);
    show_data(h->r, print_func);
}

void aho_show_data(void (*print_func)(AHO_TYPE)) {
    show_data(head, print_func);
    printf("\n");
}

void show_tree(aho *h, int depth, void (*print_func)(AHO_TYPE)) {
    if (h == z) return;
    show_tree(h->r, depth+1, print_func);
    for (int i=0; i<depth; ++i) printf("  ");
    print_func(h->data);
    printf("\n");
    show_tree(h->l, depth+1, print_func);
}

void aho_show_tree(void (*print_func)(AHO_TYPE)) {
    show_tree(head, 0, print_func);
}

void count(aho *h) {
    if (h == z) return;
    count(h->l);
    if (h->data != aho_nulldata) head->N++;
    count(h->r);
}

int aho_count(void) {
    head->N = 0;
    count(head);
    return head->N;
}

aho *search(aho *h, AHO_TYPE data, int w) {
  if (h == z) return aho_nullitem;
  if ((h->l == z) && (h->r == z)) return (data == h->data) ? h : aho_nullitem;
  if (digit(data, w) == 0) return search (h->l, data, w + 1);
  else return search (h->r, data, w + 1);
}

aho *aho_search(AHO_TYPE data) {
  return search(head, data, 0);
}

aho *split(aho *p, aho *q, int w) {
    aho *t = NEW(aho_nulldata, z, z, 2);
    switch (digit(p->data, w) * 2 + digit(q->data, w)) {
        case 0:
            t->l = split(p, q, w + 1);
            break;
        case 1:
            t->l = p;
            t->r = q;
            break;
        case 2:
            t->r = p;
            t->l = q;
            break;
        case 3:
            t->r = split(p, q, w + 1);
            break;
    }
    return t;
}

aho *insert(aho *h, AHO_TYPE data, int w) {
    if (h == z) return NEW(data, z, z, 1);
    if ((h->l == z) && (h->r == z)) return split(NEW(data, z, z, 1), h, w);
    if (!digit(h->data, w)) h->l = insert(h->l, data, w + 1);
    else h->r = insert(h->r, data, w + 1);
    return h;
}

void aho_insert(AHO_TYPE data) {
    head = insert(head, data, 0);
}
