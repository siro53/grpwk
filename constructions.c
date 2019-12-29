//
// Created by world on 2019/12/07.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constructions.h"
#pragma GCC optimize("O3")

int comp(const void *p, const void *q)
{
    return ((string_s *)q)->len - ((string_s *)p)->len;
}

void ConstructSMatrix(string_s *s_i, int matsize)
{
    printf("Accepted input text\n");
    qsort(s_i, matsize, sizeof(string_s), comp);
    printf("s_i sort complete\n");
}

void ConstructTout(string_out *t_out, char *t_temp)
{
    strcpy(t_out->str, t_temp);
    int i;
    for (i = 0; t_temp[i] != '\0'; i++)
    {
        t_out->str[i] = 'x';
    }
    //printf("Preparing output text structure\n");
}

void ConstructTin(string_out *t_in, char *t_temp)
{
    strcpy(t_in->str, t_temp);
    int i, j, start = 0, temp_id = -1;
    if (t_temp[0] == 'x')
    {
        for (i = 0; t_temp[i] == 'x'; i++)
            start = i;
    }
    for (i = start; t_temp[i] != '\0'; i++)
    {
        if (t_temp[i] == 'x')
        {
            temp_id = i - 1;
            for (j = 1; t_temp[i - 1 + j] == 'x'; j++)
            {
                t_in->shift_var[i - 1 + j] = j;
            }
            i += j - 1;
        }
    }
    //printf("Preparing input text structure\n");
}

/*


Link NEW(Item item, Link f, Link b)
{
    Link x = malloc(sizeof *x);
    x->item = item;
    x->f = f;
    x->b = b;
    return x;
}

void ConstructDLL(char s[120], int n)
{
    Item temp;
    key(temp) = n;
    strcpy(temp.Str, s);

    if (head == NULL)
    {
        head = NEW(temp, NULL, tail, 0);
        tail = head;
    }
    else
    {
        tail->b = NEW(temp, tail, NULL, 0);
        tail = tail->b;
    }
}

void Assign(string_s *S_temp, Link link_temp, int n)
{
    if (link_temp == tail)
    {
        strcpy(S_temp[n].str, (link_temp->item).Str);
        S_temp[n].len = strlen((link_temp->item).Str);
    }
    else
    {
        Assign(S_temp, link_temp->b, n + 1);
        strcpy(S_temp[n].str, (link_temp->item).Str);
        S_temp[n].len = strlen((link_temp->item).Str);
    }
}

int comp(const void *p, const void *q)
{
    //printf("compared\n");
    return ((string_s *)q)->len - ((string_s *)p)->len;
}

void ConstructSMatrix(int n)
{
    string_s *S_temp;
    S_temp = malloc(sizeof(string_s *) * n);
    S = S_temp;
    Assign(S, head, 0);
    qsort(S, n, sizeof(string_s), comp);
    printf("sort complete\n");
}
 */