#ifndef QUEUE_H
#define QUEUE_H

#define QUE_TYPE int
#define MAX_SIZE 500000

typedef struct
{
    QUE_TYPE data[MAX_SIZE];
    int front;
    int back;
} queue;

void que_init(queue *);
void que_push(queue *, QUE_TYPE);
QUE_TYPE que_pop(queue *);
int que_size(queue *);
void printQue(queue *);

#endif