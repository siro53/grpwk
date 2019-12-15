//
// Created by world on 2019/12/07.
//
#include <stdlib.h>
#include <string.h>
#include "../string_info.h"
#include "grpwk.h"
#include "../constructions.h"
#include "BM.h"
#include <stdio.h>
#include <time.h>
#include <assert.h>

//文字の比較に使用　単に見栄えを良くしてるだけ
#define ignore -1
#define success 1
#define failure 0

//これより短いs_iは処理しない
#define Min_len 31

#define High(A, B) (A > B) ? A : B

void BM_main(string_out *t_in, string_s *s, int s_size, int s_id, string_out *t_out);

int BMcomp(char tc, char sc);

void Detect(string_s s_i, string_out *t_out, int detection_id);

void BM_entrance(string_out *t_in, string_s *s, int s_size, int s_id, string_out *t_out)
{
    BM_main(t_in, s, s_size, s_id, t_out);
}

void BM_exit(string_out *t_in, string_s *s, int s_size, int s_id, string_out *t_out)
{
    //printf("BM complete: %s\n",t_out->str);
    //template_entrance(t, s, s_size, s_id, t_out);
}

/*
double gettimeofday_sec(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6
}
*/
int BMcomp(char tc, char sc)
{
    int flag;
    if (tc == 'x')
        flag = ignore;
    else if (tc == sc)
        flag = success;
    else
        flag = failure;
    return flag;
}

void Detect(string_s s_i, string_out *t_out, int detection_id)
{
    printf("DetectTest\n");
    /*
    int i,j;
    for (i = s_i.len - 1, j = 0; i < 0; i--, j++){
        printf("t_out:%s\n",t_out.str);
        t_out->str[detection_id - j] = s_i.str[i];
    }

    t_out->shift_var[detection_id - j] = s_i.len;
    */
}

int shift(char c, string_s *s_i, int comp_var)
{
    int i = 0;
    for (i = 0; 1; i++)
    {
        if ((s_i->str[s_i->len - 1 - comp_var - i] == c) || (s_i->len - 1 - comp_var - i < 0))
            break;
    }
    return i;
}

void makeShiftTable(int table[][4], string_s *s_i, int len)
{
    int i, j;
    for (i = 0; i < len - 1; i++)
    {
        for (j = 0; j < 4; j++)
        {
            table[i][j] = shift((char)(j + 'a'), s_i, i);
        }
    }
}

//int next(string_out *t_in, int *comp_var, int *point, int *t_id,string_s *s_i, int table[110][4], int **indextable ,int index, int *tail)
int next(string_out *t_in, int *comp_var, int *point, int *t_id, string_s *s_i, int table[110][4], int **indextable, int index, int *tail)
{
    int temp;

    if (1 /*t_in->str[*t_id] == 'x'*/)
    {
        if (*t_id > indextable[index][*tail])
            *tail++;
        if ((t_in->str[*point] - 'a' < 4) && (t_in->str[*point] - 'a' >= 0) && (*t_id - *point + 1 >= 0) &&
            (*t_id - *point + 1 < s_i->len))
            temp = High(table[*t_id - *point + 1][t_in->str[*point] - 'a'] + 1,
                        table[*comp_var][t_in->str[*t_id - *comp_var] - 'a']);
        else
        {
            temp = shift(t_in->str[*t_id - *comp_var], s_i, *comp_var);
        }
        temp += *t_id;
        return temp;
    }
    else
    {
        *tail += 1;
        assert(*tail < 80000);
        return indextable[index - 1][*tail];
    }
}
//
int testnum = 0;
int BM(string_out *t_in, string_s *s_i, string_out *t_out, int **indextable, int index)
{
    //t_id:s_iの最後尾がいる場所 esc:一致した文字の個数 comp_var:何回比較したか
    int t_id = s_i->len - 1, esc = 0, comp_var = 0, point = t_id, lens_i = s_i->len, tail = 0;
    int table[110][4];
    assert(index < 64);
    makeShiftTable(table, s_i, lens_i);
    while (indextable[index][tail] < t_id)
    {
        tail++;
    }

    t_id = indextable[index][tail];

    while (1 /*t_id <= T_LENGTH*/)
    {
        int flag = 1;
        //s_xが検出済で既に挿入されている場合、挿入済箇所をスキップ
        if (t_out->str[t_id] != 'x')
        {
            t_id += t_out->shift_var[t_id - lens_i];
            point = t_id;
        }
        //s_iが指定位置t_idにマッチするか確認
        while ((flag == 1) && (esc < 25) && (lens_i - 1 - comp_var >= 0) && (t_id < T_LENGTH))
        {
            switch (BMcomp(t_in->str[t_id - comp_var], s_i->str[lens_i - 1 - comp_var]))
            {
            case ignore:
                comp_var += t_in->shift_var[t_id - comp_var];
                point -= comp_var;
                break;

            case success:
                esc++;
                comp_var++;
                break;

            case failure:
                flag = 0;
                esc = 0;
                break;
            }
        }
        //マッチした場合t_outに挿入,そうでないなら次の場所を探索
        if (flag == 1)
        {
            int x, y;
            for (x = lens_i - 1, y = 0; x >= 0; x--, y++)
                t_out->str[t_id - y] = s_i->str[x];
            t_out->shift_var[t_id - y] = lens_i;
            return 0;
        }
        else
        {
            t_id = next(t_in, &comp_var, &point, &t_id, s_i, table, indextable, index, &tail);
            comp_var = 0;
            point = t_id;
        }
    }

    printf("error: s_i did not match anywhere in T\n");
    return -1;
}

void makeBigramTable(string_out *t_in, char index[][3])
{
}

int getRKShiftVar(string_out *t_in, int i)
{
    int j;
    //printf("test%c ",t_in->str[i]);
    for (j = i; t_in->str[j] == 'x'; j++)
    {
        //printf("++ ");
    }
    return j - i + 1;
}

void RK_index(string_out *t_in, int *index, int **indextable, int *indextail)
{
    int i, j, hash = (t_in->str[0] - 'a') * 9409 + (t_in->str[1] - 'a') * 97 + (t_in->str[2] - 'a'), t_id = 2;
    //assign index aaa to ddd
    for (i = 0; i < 64; i++)
    {
        //debug: printf("%c%c%c\n",(i / 16) +'a',((i / 4) % 4)+'a',(i % 4)+'a');
        index[i] = (i / 16) * 9409 + ((i / 4) % 4) * 97 + (i % 4);
        //debug: printf("j:%d %d\n",i,index[i]);
        indextail[i] = 0;
    }
    //aaaa
    if (t_in->str[2] == 'x')
    {
        t_id += getRKShiftVar(t_in, 2);
        t_id += t_in->shift_var[t_id];
        hash = (t_in->str[t_id - 2] - 'a') * 9409 + (t_in->str[t_id - 1] - 'a') * 97 + (t_in->str[t_id] - 'a');
    }
    //aaaa
    for (i = 2; i < strlen(t_in->str); i++)
    {
        if (t_in->str[i] == 'x')
        {
            for (j = 0; j < 64; j++)
            {
                indextable[j][indextail[j]++] = i;
            }
            //printf("b:%d ",i);
            i += getRKShiftVar(t_in, i);
            //printf("a:%d\n",i);
            hash = (t_in->str[i - 1] - 'a') * 9409 + (t_in->str[i] - 'a') * 97 + (t_in->str[i + 1] - 'a');

            //i += t_in->shift_var[i] + 1;
        }
        else
        {
            //debug: printf("j:%d %d\n",j,hash);
            //debug: printf("%c%c%c\n", t_in->str[i - 2], t_in->str[i - 1], t_in->str[i]);
            for (j = 0; j < 64; j++)
            {
                if (hash == index[j])
                {
                    //debug: printf("%d\n", j);
                    indextable[j][indextail[j]++] = i;
                }
            }
            //debug: printf("0:%d, ",hash);
            hash -= (t_in->str[i - 2] - 'a') * 9409;
            //debug: printf("1:%d, ",hash);
            hash *= 97;
            //debug: printf("2:%d, ",hash);
            hash += t_in->str[i + 1] - 'a';
            //debug: printf("3:%d\n",hash);
        }
    }
}

void BM_main(string_out *t_in, string_s *s, int s_size, int s_id, string_out *t_out)
{
    unsigned long int start, end;
    start = clock();
    int index[64], indextail[64];      //have hash values
    int **indextable, *indextablebase; //have index offset
    int i;

    indextable = malloc(sizeof(int *) * 64);
    indextablebase = malloc(sizeof(int) * 64 * 80000);
    for (i = 0; i < 64; i++)
    {
        indextable[i] = indextablebase + i * 80000;
    }

    RK_index(t_in, index, indextable, indextail);
    //for(i=0;i<64;i++)printf("%d: %d\n",i,index[i]);
    string_s s_iBase, *s_i;
    s_i = &(s_iBase);
    end = clock();
    printf("T:%lf\n", (double)(end - start) / CLOCKS_PER_SEC);
    for (i = 0; s[s_id + i].len > Min_len; i++)
    {
        //if (i > 4) break;
        s_i = &s[s_id + i];

        int s_index_hash = (s_i->str[s_i->len - 1] - 'a') + (s_i->str[s_i->len - 2] - 'a') * 97 +
                           (s_i->str[s_i->len - 3] - 'a') * 9409;
        //printf("index:%d\n",s_index_hash);
        int j;
        for (j = 0; j < 64; j++)
        {
            if (index[j] == s_index_hash)
            {
                printf("i:%d: len:%d %c%c%c\n", i, s_i->len, s_i->str[s_i->len - 3], s_i->str[s_i->len - 2], s_i->str[s_i->len - 1]);
                break;
            }
        }
        assert(j < 64);
        int temp = BM(t_in, s_i, t_out, indextable, j);
    }
    s_id += i;
    free(indextable);
    free(indextablebase);
    BM_exit(t_in, s, s_size, s_id, t_out);
    //printf("\nDetected s_i count:%d :%d\n",count[0],count[1]);
}

int main(void)
{
    unsigned long int start, end;
    start = clock();
    string_s *s;
    string_out Base, *t_out, inBase, *t_in;
    t_out = &Base;
    t_in = &inBase;
    s = malloc(sizeof(string_s) * 50000);
    int n = 1;

    char t[T_LENGTH];
    FILE *fp_in;
    FILE *fp_out;
    char fname[] = "../data/dat0_in";
    char fnameout[] = "dat0_out.txt";
    fp_in = fopen(fname, "r");
    if (fp_in == NULL)
    {
        printf("???");
    }
    fp_out = fopen(fnameout, "w");
    if (fp_out == NULL)
    {
        printf("???");
    }

    // input t
    fscanf(fp_in, "%s", t);

    // input s[]
    int counter = 0;
    for (; fscanf(fp_in, "%s", s[counter].str) != EOF; ++counter)
    {
        s[counter].len = strlen(s[counter].str);
    }

    ConstructSMatrix(s, counter);
    ConstructTout(t_out, t);
    ConstructTin(t_in, t);

    BM_entrance(t_in, s, 2, 0, t_out);
    int i = 0;
    for (i = 0; i < T_LENGTH; i++)
    {
        if (t_in->str[i] != 'x')
            t_out->str[i] = t_in->str[i];
        if (t_out->str[i] == 'x')
            t_out->str[i] = 'a';
    }

    fprintf(fp_out, "%s\n", t_out->str);
    end = clock();

    printf("time:%lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
