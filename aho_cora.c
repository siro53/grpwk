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
    head = (z = NEW(aho_nullitem, NULL, NULL, 0));
}

void show(aho *h, int depth) {
    if (h == z) return;
    show(h->r, depth+1);
    for (int i=0; i<depth; ++i) printf("\t");
    printf("(%d)\n", h->data);
    show(h->l, depth+1);
}

void aho_show(void) {
    show(head, 0);
}

aho *split(aho *p, aho *q, int w) {
    aho *t = NEW(aho_nullitem, z, z, 2);
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