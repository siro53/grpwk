#pragma once

#ifndef QUEUE_H
#define QUEUE_H

#define QUE_TYPE int
#define MAX_SIZE 500000

typedef struct
{
    QUE_TYPE data[MAX_SIZE];
    int front;
    int back;
    int size;
} queue;

void que_init(queue *);
void que_push(queue *, QUE_TYPE);
QUE_TYPE que_pop(queue *);
void printQue(queue *);

#endif