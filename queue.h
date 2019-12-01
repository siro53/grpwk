#pragma once

#include "ahotrie.h"

#define QUE_TYPE aho_node*
#define MAX_SIZE 500000

typedef struct
{
    QUE_TYPE data[MAX_SIZE];
    QUE_TYPE front;
    QUE_TYPE back;
} queue;

void que_init(queue *que, QUE_TYPE init_value);
void que_push(queue *que, QUE_TYPE value);
QUE_TYPE que_pop(queue *que);
int que_size(queue *que);