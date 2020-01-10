#pragma once

typedef struct _linked_node {
    int data, place;
    struct _linked_node *next, *prev;
} linked_node;

typedef struct {
    linked_node *top, *bottom;
    int length;
} linked_list;

void linked_init(linked_list *l);
void linked_destroy(linked_list *l);

int linked_push_int(linked_list *l, int data, int search);
int linked_unshift_int(linked_list *l, int data, int search);
int linked_seek_int(linked_list *l, int index);
int linked_pop_int(linked_list *l, int index);

int linked_push_node(linked_list *l, int data, int place, int search);
int linked_unshift_node(linked_list *l, int data, int place, int search);
linked_node *linked_seek_node(linked_list *l, int index);
linked_node *linked_pop_node(linked_list *l, int index);

void linked_extend(linked_list *a, linked_list *b);

int linked_delete_int(linked_list *l, int data);

void linked_print(linked_list *l);
