#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void que_init(queue *que, QUE_TYPE init_value)
{
    memset(que->data, init_value, sizeof(queue));
    que->front = 0;
    que->back = 0;
}

void que_push(queue *que, QUE_TYPE value)
{
    
}

QUE_TYPE que_pop(queue *que)
{
}

int que_size(queue *que)
{
}