#pragma once

#include "ahotrie.h"

#ifndef QUEUE_H
#define QUEUE_H

#define QUE_TYPE aho_node*
#define MAX_SIZE 500000

typedef struct
{
    QUE_TYPE *data;
    int front;
    int back;
    int size;
} queue;

void que_init(queue *);
void que_push(queue *, QUE_TYPE);
QUE_TYPE que_pop(queue *);
void que_destroy(queue *);
// void printQue(queue *);

#endif
