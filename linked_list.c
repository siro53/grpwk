#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

linked_node *linked_node_init(int data) {
    linked_node *tmp = (linked_node *)malloc(sizeof(linked_node));
    tmp->data = data;
    tmp->place = 0;
    return tmp;
}

void linked_init(linked_list *l) {
    l->length = 0;
}

void linked_destroy(linked_list *l) {
    while (l->length != 0) free(linked_pop_node(l, 0));
}

int linked_search_int(linked_list *l, int data) {
    linked_node *iter = l->top;
    for (int v=0; v<l->length; v++, iter=iter->next) {
        if (iter->data == data) return 1;
    }
    return 0;
}

int linked_search_node(linked_list *l, int data, int place) {
    linked_node *iter = l->top;
    for (int v=0; v<l->length; v++, iter=iter->next) {
        if (iter->data == data && iter->place == place) return 1;
    }
    return 0;
}

// insert data to bottom of list
int linked_push_int(linked_list *l, int data, int search) {
    if (search && linked_search_int(l, data)) return 0;
    linked_node *tmp = linked_node_init(data);
    if (l->length++ == 0) {
        l->top = tmp;
        l->bottom = tmp;
    } else {
        l->bottom->next = tmp;
        tmp->prev = l->bottom;
        l->bottom = tmp;
    }
    return 1;
}

// insert data to top of list
int linked_unshift_int(linked_list *l, int data, int search) {
    if (search && linked_search_int(l, data)) return 0;
    linked_node *tmp = linked_node_init(data);
    if (l->length++ == 0) {
        l->top = tmp;
        l->bottom = tmp;
    } else {
        l->top->prev = tmp;
        tmp->next = l->top;
        l->top = tmp;
    }
    return 1;
}

// look at data of index (negative value for looking from the bottom: -1:=l->bottom->data)
int linked_seek_int(linked_list *l, int index) {
    if (index == 0) return l->top->data;
    else if (index == -1) return l->bottom->data;
    else if (index > 0) {
        linked_node *iter = l->top->next;
        for (int i=1; i<index; i++) iter = iter->next;
        return iter->data;
    } else if (index < 0) {
        linked_node *iter = l->bottom->prev;
        for (int i=-2; i>index; i--) iter = iter->prev;
        return iter->data;
    }
    return 0;
}

// delete the data of index and return (negative value for counting from the bottom: -1=l->bottom->data)
int linked_pop_int(linked_list *l, int index) {
    linked_node *iter = NULL;
    if (index == 0) {
        iter = l->top;
        l->top = iter->next;
    } else if (index == -1) {
        iter = l->bottom;
        l->bottom = iter->prev;
    } else {
        if (index > 0) {
            iter = l->top->next;
            for (int i=1; i<index; i++) iter = iter->next;
        } else {
            iter = l->bottom->prev;
            for (int i=-2; i>index; i--) iter = iter->prev;
        }
        iter->prev->next = iter->next;
        iter->next->prev = iter->prev;
    }
    if (iter != NULL) {
        l->length--;
        int data = iter->data;
        free(iter);
        return data;
    } else return 0;
}

// insert data and place to bottom of list
int linked_push_node(linked_list *l, int data, int place, int search) {
    if (search && linked_search_node(l, data, place)) return 0;
    linked_node *tmp = linked_node_init(data);
    tmp->place = place;
    if (l->length++ == 0) {
        l->top = tmp;
        l->bottom = tmp;
    } else {
        l->bottom->next = tmp;
        tmp->prev = l->bottom;
        l->bottom = tmp;
    }
    return 1;
}

// insert data and place to top of list
int linked_unshift_node(linked_list *l, int data, int place, int search) {
    if (search && linked_search_node(l, data, place)) return 0;
    linked_node *tmp = linked_node_init(data);
    tmp->place = place;
    if (l->length++ == 0) {
        l->top = tmp;
        l->bottom = tmp;
    } else {
        l->top->prev = tmp;
        tmp->next = l->top;
        l->top = tmp;
    }
    return 1;
}

// return node of index (negative value for looking from the bottom: -1:=l->bottom)
linked_node *linked_seek_node(linked_list *l, int index) {
    if (index == 0) return l->top;
    else if (index == -1) return l->bottom;
    else if (index > 0) {
        linked_node *iter = l->top->next;
        for (int i=1; i<index; i++) iter = iter->next;
        return iter;
    } else if (index < 0) {
        linked_node *iter = l->bottom->prev;
        for (int i=-2; i>index; i--) iter = iter->prev;
        return iter;
    }
    return NULL;
}

// delete the data of index and return (negative value for counting from the bottom: -1=l->bottom->data)
linked_node *linked_pop_node(linked_list *l, int index) {
    linked_node *iter = NULL;
    if (index == 0) {
        iter = l->top;
        l->top = iter->next;
    } else if (index == -1) {
        iter = l->bottom;
        l->bottom = iter->prev;
    } else {
        if (index > 0) {
            iter = l->top->next;
            for (int i=1; i<index; i++) iter = iter->next;
        } else {
            iter = l->bottom->prev;
            for (int i=-2; i>index; i--) iter = iter->prev;
        }
        iter->prev->next = iter->next;
        iter->next->prev = iter->prev;
    }
    if (iter != NULL) {
        l->length--;
        return iter;
    } else return NULL;
}

void linked_print(linked_list *l) {
    linked_node *iter = l->top;
    for (int v=0; v<l->length; v++, iter = iter->next) {
        printf("(%d, %d) ", iter->data, iter->place);
    }
    printf("\n");
}

int linked_delete_int(linked_list *l, int data) {
    linked_node *iter = l->top;
    for (int v=0; v<l->length; v++, iter=iter->next) {
        if (iter->data == data) {
            linked_pop_int(l, v);
            return 1;
        }
    }
    return 0;
}