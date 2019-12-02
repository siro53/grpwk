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

void que_init(queue *que, QUE_TYPE init_value);
void que_push(queue *que, QUE_TYPE value);
QUE_TYPE que_pop(queue *que);
int que_size(queue *que);
void printQue(queue *que);

#endif