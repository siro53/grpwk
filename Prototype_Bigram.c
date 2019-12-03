//
// Created by udemegane on 2019/12/02.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Udemegane_Prototype.h"
#include "Udemegane_Debug.h"

///I created s_i with a Doubly-Linked-List. If necessary,Please convert to another data structure(ex:Tree)
/*------------------------------------------------------------*/
typedef struct Node *link;
struct Node
{
    Item item;
    link f, b;
    int matched;
};
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

///Index for Bi-gram
struct List
{
    int tail;
    int id_table[N];
};

///Tin is stored here
struct String_T
{
    char str[N];
    char out[N];
};

///S_i is stored here. There are dynamic arrays. Don't forget to free up memory.
typedef struct
{
    char str[120];
    int len;
} String_S;

///This is global var. Please be careful about these handling
/*------------------------------------------------------------*/
static link head, tail;
struct List id_info[16];
static char index[16][3] = {"aa", "ab", "ac", "ad", "ba", "bb", "bc", "bd", "ca", "cb", "cc", "cd", "da", "db", "dc", "dd"};
String_S *S;
struct String_T T;
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

///DebugFunction
/*------------------------------------------------------------*/
void DebugPrint_ShowNowStr(void)
{
    printf("Debug:%s\n", (tail->item).Str);
}

void DebugPrint_All(void)
{
    link temp = head;
    while (1)
    {
        printf("String:%s tail:%d \n", (temp->item).Str, (temp == tail) ? 1 : 0);
        temp = temp->b;
        if (temp == NULL)
            break;
    }
}

void DebugPrint_ShowBGTable(char *T)
{
    int i, j = 0;
    printf("%s\n", T);
    for (i = 0; i < 16; i++)
    {
        printf("%s:{", index[i]);
        for (j = 0; j < id_info[i].tail; j++)
        {
            printf(",%d ", id_info[i].id_table[j]);
        }
        printf("}\n");
    }
}

void DebugPrint_ShowSMatrix(int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("StrofMat:%s len:%d\n", S[i].str, S[i].len);
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

///これはマクロにするべきだった　あたまわるい
char *INDEX(int n)
{
    switch (n)
    {
    case 1:
        return "aa";

    case 2:
        return "ab";

    case 3:
        return "ac";

    case 4:
        return "ad";

    case 5:
        return "ba";

    case 6:
        return "bb";

    case 7:
        return "bc";

    case 8:
        return "bd";

    case 9:
        return "ca";

    case 10:
        return "cb";

    case 11:
        return "cc";

    case 12:
        return "cd";

    case 13:
        return "da";

    case 14:
        return "db";

    case 15:
        return "dc";

    case 16:
        return "dd";
    default:
        return "";
    }
}

///Create Doubly-Linked-List for Buffer and Matrix of S_i
/*------------------------------------------------------------*/
link NEW(Item item, link f, link b, int matched)
{
    link x = malloc(sizeof *x);
    x->item = item;
    x->f = f;
    x->b = b;
    x->matched = matched;
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

        DebugPrint_ShowNowStr();
    }
    else
    {
        tail->b = NEW(temp, tail, NULL, 0);
        tail = tail->b;

        DebugPrint_ShowNowStr();
    }
}

void Assign(String_S *S_temp, link link_temp, int n)
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
    return ((String_S *)q)->len - ((String_S *)p)->len;
}

void ConstructSMatrix(int n)
{
    String_S *S_temp;
    S_temp = malloc(sizeof(String_S *) * n);
    S = S_temp;
    Assign(S, head, 0);
    qsort(S, n, sizeof(String_S), comp);
    printf("sort complete\n");
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

///Create Bi-gram Table
/*------------------------------------------------------------*/
void CreateBigramTable(struct String_T T)
{
    int i, j;

    for (i = aa; i <= dd; i++)
    {
        for (j = 0; T.str[j] != '\0'; j++)
        {
            if (j == 0)
                id_info[i].tail = 0;

            if (T.str[j] == index[i][0] && T.str[j + 1] == index[i][1])
            {
                idSearch(i, id_info[i].tail) = j;
                id_info[i].tail++;
            }
        }
    }

    char *temp;
}

void ImportT(char Tin[N])
{

    strcpy(T.str, Tin);
    CreateBigramTable(T);

    int i;
    for (i = 0; i < 33; i++)
        T.out[i] = 'x';
    T.out[33] = '\0';
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void Endcalc()
{
    int i;
    for (i = 0; i < 33; i++)
        if (T.out[i] == 'x')
            T.out[i] = 'a';

    printf("\nOUTPUT:%s\n", T.out);
}

int Mystrcmp(int id, int j)
{
    int i, counter = 0, flag = 1;
    for (i = 0; i < strlen(S[j].str); i++)
    {
        if (15 < counter)
            break;

        if (T.str[id + i] == S[j].str[i])
            continue;
        else if (T.str[id + i] == 'x')
        {
            counter++;
            continue;
        }
        else
        {
            flag = 0;
            break;
        }
    }

    if (flag == 1)
        for (i = 0; i < strlen(S[j].str); i++)
            T.out[id + i] = S[j].str[i];

    return flag;
}

void Search_s(int i)
{
    int j;
    for (j = 0; j < id_info[i].tail; j++)
    {
        int flag;
        if (T.out[id_info[i].id_table[j]] == 'x')
            continue;
        flag = Mystrcmp(id_info[i].id_table[j], i);
        if (flag == 1)
            break;
    }
}

void IndexSearch(int n)
{
    int i, j;
    for (i = 0; i <= n; i++)
    {
        for (j = aa; j <= dd; j++)
        {
            if (S[i].len < 4)
            {
                Endcalc();
                return;
            }
            if (strncmp(INDEX(j), S[i].str, 2) == 0)
            {
                Search_s(j);
                break;
            }
            else
                continue;
        }
    }
}

void Endfunc(void)
{
    free(S);
}
