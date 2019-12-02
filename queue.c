#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <string.h>

void que_init(queue *que, QUE_TYPE init_value)
{
    que->front = 0;
    que->back = 0;
    int i;
    for (i = 0; i < MAX_SIZE; i++)
    {
        que->data[i] = init_value;
    }
}

void que_push(queue *que, QUE_TYPE value)
{
    if (que->back >= MAX_SIZE)
    {
        printf("キューの容量がいっぱいです\n");
        return;
    }
    que->data[que->back] = value;
    que->back++;
}

QUE_TYPE que_pop(queue *que)
{
    if (que->front >= que->back)
    {
        printf("キューの中身は空です\n");
        return -1;
    }
    QUE_TYPE top = que->data[que->front];
    que->front++;
    return top;
}

int que_size(queue *que)
{
    return (que->back - que->front);
}

void printQue(queue *que)
{
    int i;
    printf("data : ");
    for (i = que->front; i < que->back; i++)
    {
        printf("%d ", que->data[i]);
    }
    printf("\n");
}
