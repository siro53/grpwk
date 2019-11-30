#include <stdio.h>
#include "queue.h"

struct hoge{
    int data[20];
    int num;
};

int main()
{
    int i, a;
    queue q;
    que_init(&q, -1);
    for (i = 0; i < 5; i++)
    {
        que_push(&q, i + 1);
        printQue(&q);
    }
    for (i = 0; i < 3; i++)
    {
        a = que_pop(&q);
        printf("%d\n", a);
    }
    printQue(&q);
    printf("%d\n", que_size(&q));
    return 0;
}