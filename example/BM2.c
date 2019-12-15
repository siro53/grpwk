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
#define Min_len 20

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
int error = 0;
int BM(string_out *t_in, string_s *s_i, string_out *t_out)
{

    //t_id:s_iの最後尾がいる場所 esc:一致した文字の個数 comp_var:何回比較したか
    int t_id = s_i->len - 1, esc = 0, comp_var = 0, point = t_id, lens_i = s_i->len;
    int table[110][4];
    makeShiftTable(table, s_i, lens_i);

    while (1 /*t_id - 1<= T_LENGTH*/)
    {
        int flag = 1;
        //s_xが検出済で既に挿入されている場合、挿入済箇所をスキップ
        if (t_out->str[t_id] != 'x')
        {
            t_id += t_out->shift_var[t_id - lens_i];
            point = t_id;
        }
        //s_iが指定位置t_idにマッチするか確認
        while ((flag == 1) && (esc < 25) && (lens_i - 1 - comp_var >= 0) && (t_id < T_LENGTH /*strlen(t_in->str)*/))
        {
            /*----------------------DebugPrint-------------------------*/
            /*---------------------------------------------------------*/
            /*
            printf("t_s:");
            int j;
            for(j=0;j<strlen(t_in->str);j++)
                printf("%d",t_out->shift_var[j]);
            printf("\nt  :%s\n",t_in->str);
            printf("out:%s\n",t_out->str);
            printf("s_i:");

            for(j=0;j<t_id-s_i->len+1;j++)
                printf(" ");
            printf("%s\n",s_i->str);
            printf("cmp:");
            for(j=0;j<t_id-comp_var;j++)
                printf(" ");
            printf("^\n");
            printf("pnt:");
            for(j=0;j<point;j++)
                printf(" ");
            printf("^\n");
            printf("t_id:%d  comp_var:%d\n",t_id,comp_var);
            /*---------------------------------------------------------*/
            /*---------------------------------------------------------*/
            switch (BMcomp(t_in->str[t_id - comp_var], s_i->str[lens_i - 1 - comp_var]))
            {
            case ignore:
                comp_var += t_in->shift_var[t_id - comp_var];
                point = t_id - comp_var;
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
            if (lens_i - 1 - comp_var < 0)
            {
                error++;
            }
        }
        //マッチした場合t_outに挿入,そうでないなら次の場所を探索
        if (flag == 1)
        {
            int x, y;
            for (x = lens_i - 1, y = 0; x >= 0; x--, y++)
            {
                t_out->str[t_id - y] = s_i->str[x];
                t_out->shift_var[t_id - y] = lens_i - x - 1;
                if (s_i->str[x] != t_in->str[t_id - y])
                    printf("なにかおかしい\n");
            }
            t_out->shift_var[t_id - y] = lens_i;
            return 0;
        }
        else
        {
            int temp;
            if ((t_in->str[point] - 'a' < 4) && (t_in->str[point] - 'a' >= 0) && (t_id - point + 1 >= 0) &&
                (t_id - point + 1 < lens_i))
            {

                temp = High(table[t_id - point + 1][t_in->str[point] - 'a'] + 1,
                            table[comp_var][t_in->str[t_id - comp_var] - 'a']);

                //temp = table[comp_var][t_in->str[t_id - comp_var] - 'a'];
            }
            else
            {
                temp = shift(t_in->str[t_id - comp_var], s_i, comp_var);
            }
            t_id += temp;
            comp_var = 0;
            point = t_id;
            //assert(t_id<T_LENGTH+1);
        }
    }

    printf("error: s_i did not match anywhere in T\n");
    return -1;
}

void makeBigramTable(string_out *t_in, char index[][3])
{
}

void BM_main(string_out *t_in, string_s *s, int s_size, int s_id, string_out *t_out)
{
    unsigned long int start, end;
    start = clock();
    int i, j = 0;
    //char index[16][3] = {"aa", "ab", "ac", "ad", "ba", "bb", "bc", "bd", "ca", "cb", "cc", "cd", "da", "db", "dc", "dd"}; //[][0]:１文字目　[][1]:２文字目　[][2]:終端文字
    //link head;
    string_s s_iBase, *s_i;
    s_i = &(s_iBase);
    end = clock();
    //printf("T:%lf\n", (double)(end - start) / CLOCKS_PER_SEC);
    for (i = 0; s[s_id + i].len > Min_len; i++)
    {
        //if (i > 4) break;
        s_i = &s[s_id + i];
        //printf("len:%d\n",s_i->len);
        int temp = BM(t_in, s_i, t_out);
        //printf(" i:%d Save:%.2f Slen:%d\n", i, shiftave / i, lensum);
        if (temp == -1)
            printf("s_id:%d len:%d\n", s_id + i, s_i->len);
    }
    s_id += i;
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
    //char fname[] = "../data/test.txt";
    char fname[] = "../data/dat0_in";
    //char fnameout[] = "out.txt";
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
    int i = 0, Fcount = 0;
    for (i = 0; i < T_LENGTH; i++)
    {
        if (t_in->str[i] != 'x')
        {
            if (t_out->str[i] != 'x')
                Fcount++;
        }
    }
    printf("fault:%d\n", Fcount);
    BM_entrance(t_in, s, 2, 0, t_out);
    Fcount = 0;
    for (i = 0; i < T_LENGTH; i++)
    {
        if (t_in->str[i] != 'x')
        {
            if (t_out->str[i] != 'x')
                Fcount++;
            t_out->str[i] = t_in->str[i];
        }

        if (t_out->str[i] == 'x')
            t_out->str[i] = 'a';
    }
    printf("fault:%d error:%d\n", Fcount, error);
    fprintf(fp_out, "%s\n", t_out->str);
    end = clock();

    printf("time:%lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
