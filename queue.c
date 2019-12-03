#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <string.h>

void que_init(queue *que)
{
    que->front = 0;
    que->back = 0;
    que->size = 0;
}

void que_push(queue *que, QUE_TYPE value)
{
    if (que->back >= MAX_SIZE)
    {
        printf("キューの容量がいっぱいです\n");
        return;
    }
    que->data[que->back] = value;
    que->back = (que->back + 1) % MAX_SIZE;
    que->size++;
}

QUE_TYPE que_pop(queue *que)
{
    if (que->front >= que->back)
    {
        printf("キューの中身は空です\n");
        return -1;
    }
    QUE_TYPE top = que->data[que->front];
    que->front = (que->front + 1) % MAX_SIZE;
    que->size--;
    return top;
}

void printQue(queue *que)
{
    int i;
    printf("data : ");
    for (i = que->front; i < que->back; i++)
    {
        printf("%p ", que->data[i]);
    }
    printf("\n");
}
