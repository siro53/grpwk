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
#include <pthread.h>
#include <sys/time.h>
#include <sys/times.h>

//文字の比較に使用　単に見栄えを良くしてるだけ
#define ignore -1
#define success 1
#define failure 0

//これより短いs_iは処理しない
#define Min_len 19
#define ThreadNum 8

#define High(A, B) (A > B) ? A : B
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

typedef struct
{
    string_out *t_in;
    string_s *s;
    string_out *t_out;
    int skipnum;
} Fthreadstructure;

void BM_main(string_out *t_in, string_s *s, int s_size, int s_id, string_out *t_out);

//int BMcomp(char tc, char sc);

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
/*
int BMcomp(char tc, char sc) {
    int flag;
    if (tc == 'x')
        flag = ignore;
    else if (tc == sc)
        flag = success;
    else
        flag = failure;
    return flag;
}

int shift(char c, string_s *s_i, int comp_var) {
    int i = 0;
    for (i = 0; 1; i++) {
        if ((s_i->str[s_i->len - 1 - comp_var - i] == c) || (s_i->len - 1 - comp_var - i < 0))
            break;
    }
    return i;
}

void makeShiftTable(int table[][4], string_s *s_i, int len) {
    int i, j;
    for (i = 0; i < len - 1; i++) {
        for (j = 0; j < 4; j++) {
            table[i][j] = shift((char) (j + 'a'), s_i, i);
        }
    }
}
*/

clock_t times_clock()
{
    struct tms t;
    return times(&t);
}

// for debug
//int error = 0, g_s_id, g_s_len, g_s_lensum = 0;

void *BM(void *Ft_in)
{
    //clock_t t1,t2;
    //t1 = times_clock();
    Fthreadstructure *Ft = (Fthreadstructure *)Ft_in;
    string_out *t_in = Ft->t_in;
    string_s *s = Ft->s;
    string_out *t_out = Ft->t_out;
    int i, t_id, esc, comp_var, point, lens_i;
    string_s s_iBase, *s_i;
    s_i = &(s_iBase);
    int tnum = Ft->skipnum;
    for (i = 0; 1; i++)
    {
        s_i = &s[ThreadNum * i + tnum];
        /* //debugprint
        g_s_id = i;
        g_s_len = s_i->len;
        g_s_lensum += s_i->len;
        */

        //t_id:s_iの最後尾がいる場所
        t_id = s_i->len - 1;
        //esc:一致した文字の個数
        esc = 0;
        //comp_var:何回比較したか
        comp_var = 0;
        //比較済みの文字の中で
        point = t_id;
        lens_i = s_i->len;
        int table[110][4];

        //makeShiftTable
        int k;
        for (k = 0; k < lens_i - 1; k++)
        {
            int Tcounter;
            rep(j, 120)
            {
                Tcounter = j;
                if ((s_i->str[s_i->len - 1 - k - j] == (0 + 'a')) || (s_i->len - 1 - k - j < 0))
                    break;
            }
            table[k][0] = Tcounter;
            rep(j, 120)
            {
                Tcounter = j;
                if ((s_i->str[s_i->len - 1 - k - j] == (1 + 'a')) || (s_i->len - 1 - k - j < 0))
                    break;
            }
            table[k][1] = Tcounter;
            rep(j, 120)
            {
                Tcounter = j;
                if ((s_i->str[s_i->len - 1 - k - j] == (2 + 'a')) || (s_i->len - 1 - k - j < 0))
                    break;
            }
            table[k][2] = Tcounter;
            rep(j, 120)
            {
                Tcounter = j;
                if ((s_i->str[s_i->len - 1 - k - j] == (3 + 'a')) || (s_i->len - 1 - k - j < 0))
                    break;
            }
            table[k][3] = Tcounter;
        }

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
            int whiletest = 0;

            while ((flag == 1) && (esc < 21) && (lens_i - 1 - comp_var >= 0) &&
                   (t_id < T_LENGTH /*strlen(t_in->str)*/))
            {
                whiletest = 1;
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

                if (t_in->str[t_id - comp_var] == 'x')
                {
                    //ignore
                    comp_var += t_in->shift_var[t_id - comp_var];
                    point = t_id - comp_var;
                }
                else if (t_in->str[t_id - comp_var] == s_i->str[lens_i - 1 - comp_var])
                {
                    //success
                    esc++;
                    comp_var++;
                }
                else
                {
                    //failware
                    flag = 0;
                    esc = 0;
                }
            }
            /*
            if (whiletest == 0) {
                printf("なにかおかしいよ:%d :%d\n", g_s_id, g_s_len);
                printf("t_id < T_LENGTH:%d\n", t_id < T_LENGTH);
            }
            */
            //マッチした場合t_outに挿入,そうでないなら次の場所を探索
            if (flag == 1)
            {
                if (whiletest == 1)
                {
                    int x, y, f = 0;

                    for (x = lens_i - 1, y = 0; x >= 0; x--, y++)
                    {
                        t_out->str[t_id - y] = s_i->str[x];
                        t_out->shift_var[t_id - y] = lens_i - x - 1;
                    }

                    t_out->shift_var[t_id - y] = lens_i;
                }
                esc = 0;
                goto next;
            }
            else
            {
                int temp;
                temp = High(table[t_id - point + 1][t_in->str[point] - 'a'] + 1,
                            table[comp_var][t_in->str[t_id - comp_var] - 'a']);
                /*
                if ((t_in->str[point] - 'a' < 4) && (t_in->str[point] - 'a' >= 0) ) {
                    temp = High(table[t_id - point + 1][t_in->str[point] - 'a'] + 1,
                                table[comp_var][t_in->str[t_id - comp_var] - 'a']);
                    swiftsum += temp;
                    swiftnum ++;
                } else {
                    elsecount++;
                    temp = shift(t_in->str[t_id - comp_var], s_i, comp_var);
                }
                */
                t_id += temp;
                comp_var = 0;
                point = t_id;
            }
        }

    next:
        if (lens_i <= Min_len)
        {
            break;
        }
    }
    //t2 = times_clock();
    //printf("Thread%d|time:%lf\n",tnum, (double) (t2 - t1)/100);
}

void BM_main(string_out *t_in, string_s *s, int s_size, int s_id, string_out *t_out)
{
    //printf("Start BM algorithm\n");
    pthread_t handle[ThreadNum];

    Fthreadstructure *Ft[ThreadNum], Ft_Base[ThreadNum], *Ft2, Ft2_Base;
    rep(i, ThreadNum)
    {
        Ft[i] = &(Ft_Base[i]);
        Ft[i]->t_in = t_in;
        Ft[i]->s = s;
        Ft[i]->t_out = t_out;
        Ft[i]->skipnum = i;
    }
    rep(i, ThreadNum)
    {
        pthread_create(&handle[i], NULL, BM, Ft[i]);
    }
    rep(i, ThreadNum)
    {
        pthread_join(handle[i], NULL);
    }
    //s_id += i;
    BM_exit(t_in, s, s_size, s_id, t_out);
}

int main(void)
{
    clock_t t1, t2;
    t1 = times_clock();
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
    int i = 0, Xcount = 0, Xcount2 = 0;

    BM_entrance(t_in, s, 2, 0, t_out);

    for (i = 0; i < T_LENGTH; i++)
    {
        if (t_out->str[i] == 'x')
            Xcount++;
        if (t_in->str[i] != 'x')
        {
            t_out->str[i] = t_in->str[i];
        }

        if (t_out->str[i] == 'x')
        {
            t_out->str[i] = 'a';
            Xcount2++;
        }
    }
    t_out->str[T_LENGTH] = '\0';

    if (t_out->str == NULL)
        printf("???????\n");
    fprintf(fp_out, "%s\n", t_out->str);
    t2 = times_clock();

    printf("\ntime:%lf\n", (double)(t2 - t1) / 100);
    /* //debugprint
    printf("長さ%dまでのs_iを処理\n", Min_len + 1);
    printf("割り当てた文字|lens_iの合計:%d|%d ＊一致してなければおかしい \n復元できなかった文字:%d\n編集距離の推定値1:%.f\n編集距離の推定値2:%.f\n",
            400001 - Xcount, g_s_lensum, Xcount2, Xcount2 * 0.6, (160000 - g_s_lensum * 0.4) * 0.6);
    */
    int dcounter = 0;
    FILE *fp_ref = fopen("../data/dat0_ref", "r");
    char ref[500000];
    fscanf(fp_ref, "%s", ref);
    for (int i = 0; i < T_LENGTH; i++)
        dcounter += (ref[i] != t_out->str[i]);

    printf("実際の編集距離: %d\n復元率:%.2f%c \n割り当てミス文字の概数:%.f\n", dcounter, (400001 - dcounter) / 4000.01, 37,
           (dcounter * 1.67) * 2.5 - Xcount > 0 ? (dcounter * 1.67) * 2.5 - Xcount : 0);
    //printf("^この３つの編集距離はほぼ同じじゃないと困る\n");

    return 0;
}
