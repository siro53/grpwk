//
// Created by world on 2019/12/07.
//
#pragma GCC optimize("O3")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../constructions.h"
#include "BM.h"

//これより短いs[i]は処理しない

typedef struct
{
    string_out *t_in;
    string_s *s;
    string_out *t_out;
    int skipnum;
} Fthreadstructure;

void BM(string_out *t_in, string_s *s, int to, string_out *t_out, linked_list *s_count, linked_list *t_opt)
{
    /*----------------------initialize-------------------------*/
    int t_id, esc, comp_var, point;
    /*---------------------------------------------------------*/
    for (int i = 0; i < to; i++)
    {
        string_s *s_i = &s[i];
        //t_id:s_iの最後尾がいる場所
        t_id = s_i->len - 1;
        //esc:一致した文字の個数
        esc = 0;
        //comp_var:何回比較したか
        comp_var = 0;
        //point:比較済みの文字の中で左から見てxに最も近い場所
        point = t_id;
        int table[110][4];

        /*---------------------makeShiftTable----------------------*/
        for (int k = 0; k < s_i->len - 1; k++)
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
        /*---------------------------------------------------------*/

        while (t_id - 1 <= T_LENGTH)
        {
            int flag = 1;
            //s_xが検出済で既に挿入されている場合、挿入済箇所をスキップ
            if (t_out->str[t_id] != 'x')
            {
                t_id += High(t_out->shift_var[t_id - s_i->len], t_out->shift_var[t_id]);
                point = t_id;
            }

            //s_iが指定位置t_idにマッチするか確認
            int branch = (t_in->str[t_id - comp_var] != s_i->str[s_i->len - 1 - comp_var]);
            if (((t_in->str[t_id - comp_var] != 'x') && branch))
            {
                //failware
                flag = 0;
                esc = 0;
            }
            else if (!branch)
            {
                //success
                esc++;
                comp_var++;
            }
            else
            {
                //ignore
                comp_var += t_in->shift_var[t_id - comp_var];
                point = t_id - comp_var;
            }

            while ((flag == 1) && (esc < 21) && (s_i->len - 1 - comp_var >= 0) && (t_id - comp_var != 0))
            {
                if (t_out->str[t_id] != 'x')
                {
                    t_id += High(t_out->shift_var[t_id - s_i->len], t_out->shift_var[t_id]);
                    point = t_id;
                }
                /*----------------------DebugPrint-------------------------*/
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
                branch = (t_in->str[t_id - comp_var] != s_i->str[s_i->len - 1 - comp_var]);
                if (((t_in->str[t_id - comp_var] != 'x') && branch))
                {
                    //failware
                    flag = 0;
                    esc = 0;
                }
                else if (!branch)
                {
                    //success
                    esc++;
                    comp_var++;
                }
                else
                {
                    //ignore
                    comp_var += t_in->shift_var[t_id - comp_var];
                }
            }
            //マッチした場合t_outに挿入,そうでないなら次の場所を探索
            if (flag == 1)
            {
                if (s_i->len > 24)
                {
                    int x, y;
                    for (x = s_i->len - 1, y = 0; x >= 0; x--, y++)
                    {
                        t_out->str[t_id - y] = s_i->str[x];
                        t_out->shift_var[t_id - y] = s_i->len - x - 1;
                    }
                    t_out->shift_var[t_id - y] = s_i->len;
                    esc = 0;
                    continue;
                }
                else
                {
                    //printf("%d %d\n",s[i].id,t_id);
                    linked_push_int(&s_count[s_i->id], t_id - s_i->len + 1, 0);
                    //printf("pushed\n");
                    for (int j = 0; j < s_i->len; j++)
                    {
                        linked_push_node(&t_opt[t_id - s_i->len + 1 + j], s_i->id, j, 0);
                    }
                    //printf("completed\n");
                }
            }
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
            //int temp = High(table[t_id - point + 1][(t_id == point)&&t_in->str[t_id+1]!='x'? t_in->str[point+1] - 'a':t_in->str[point] - 'a'] + 1,
            //                table[comp_var][t_in->str[t_id - comp_v ar] - 'a']);
            int temp = High(table[t_id - point + 1][t_in->str[point] - 'a'] + 1,
                            table[comp_var][t_in->str[t_id - comp_var] - 'a']);

            t_id += temp;
            comp_var = 0;
            point = t_id;
        }
    }
}
