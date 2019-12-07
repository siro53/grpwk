//
// Created by world on 2019/12/07.
//
#include <stdlib.h>
#include <string.h>
#include "../string_info.h"
#include "grpwk.h"
#include <stdio.h>

//文字の比較に使用　単に見栄えを良くしてるだけ
#define ignore -1
#define success 1
#define failure 0

//これより短いs_iは処理しない
#define Min_len 5 



void BM_main(char *t, string_s *s, int s_size, int s_id, string_out *t_out);
int BMcomp(char tc, char sc);
void Detect(string_s s_i, string_out *t_out, int detection_id);

void BM_entrance(char *t, string_s *s, int s_size, int s_id, string_out *t_out) {
    BM_main(t, s, s_size, s_id, t_out);
}

void BM_exit(char *t, string_s *s, int s_size, int s_id, string_out *t_out) {
    printf("BM complete: %s\n",t_out->str);
    template_entrance(t, s, s_size, s_id, t_out);
}

int BMcomp(char tc, char sc){
    int flag ;
    if(tc == 'x')
        flag = ignore;
    else if(tc == sc)
        flag = success;
    else
        flag = failure;
    return flag;
}

void Testfunc(void){
    printf("ok");
    return ;
}

void Detect(string_s s_i, string_out *t_out, int detection_id){
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

int shift(char c, string_s s_i, int comp_var){
    int i= 0;

    for(i=0; 1; i++){
        //printf("compare char_t:%c char_s_i:%c\n",c,s_i.str[s_i.len - 1 - comp_var - i]);
        if(s_i.str[s_i.len - 1 - comp_var - i] == c)break;
    }
    printf("\nShift s_i by %d\n\n",i);
    return i;
}

void BM(char *t, string_s s_i, string_out *t_out) {
    //t_id:s_iの最後尾がいる場所 esc:一致した文字の個数 comp_var:何回比較したか
    int t_id = s_i.len - 1, esc = 0, comp_var = 0;


    //printf("booltest%d\n",s_i.len - 1 - comp_var);
    while(t_id <= T_LENGTH){
        int flag = 1;

        //s_xが検出済で既に挿入されている場合、挿入済箇所をスキップ
        printf("Whether or not already matched|character:%c\n",t_out->str[t_id]);
        if(t_out->str[t_id] != 'x'){
            printf("Caution|Already matched:Character is not 'x',shifts s_i position\n");
            printf("out:%s\n",t_out->str);
            t_id += t_out->shift_var[t_id - s_i.len];
        }else
            printf("Did not match\n");

        //s_iが指定位置t_idにマッチするか確認
        while((flag == 1) && (esc < 15) && (s_i.len - 1 - comp_var >= 0 ) && (t_id < strlen(t))){
            printf("t  :%s\n",t);
            printf("s_i:");
            int j;
            for(j=0;j<t_id-s_i.len+1;j++)
                printf(" ");
            printf("%s\n",s_i.str);
            printf("cmp:");
            for(j=0;j<t_id-comp_var;j++)
                printf(" ");
            printf("^\n");
            printf("t_id:%d  comp_var:%d\n",t_id,comp_var);

            switch (BMcomp(t[t_id - comp_var], s_i.str[s_i.len - 1 - comp_var])){
                case ignore:
                    comp_var++;
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
        //マッチした場合st_outに挿入,そうでないなら次の場所を探索
        if (flag == 1){
            printf("\nDetected the exact position of s_i!!\n");
            //printf("Test %s\n%s\n%d\n",s_i.str,t_out.str,t_id);
            //Detect(s_i, t_out, t_id);
            printf("Before s_i assignment:%s\n",t_out->str);
            int x,y;
            for (x = s_i.len - 1, y = 0; x >= 0; x--, y++){
                t_out->str[t_id - y ] = s_i.str[x];
                //printf("t_out:%s oc:%c sc:%c\n",t_out->str,t_out->str[t_id - y],s_i.str[x]);
            }
            t_out->shift_var[t_id - y ] = s_i.len;
            printf("After  s_i assignment:%s\n\n\n",t_out->str);
            return ;


        } else{
            t_id+=shift(t[t_id - comp_var], s_i, comp_var);
            comp_var = 0;
        }

    }

    printf("error: s_i did not match anywhere in T");


}

void BM_main(char *t, string_s *s, int s_size, int s_id, string_out *t_out){
    int i;
    string_s s_i;

    for(i = 0; s[s_id+i].len > Min_len ;i++){
        s_i = s[s_id + i];
        BM(t,s_i,t_out);
    }
    s_id += i;
    BM_exit(t,s,s_size,s_id,t_out);
}
/*
int main(void){
 

    char t[] = "abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada";
    string_s s[2];
    string_out Base ,*t_out;
    t_out = &Base;


    strcpy(s[0].str,"abcddbcdbcbaaaabcccaabaaada");
    s[0].len = strlen("abcddbcdbcbaaaabcccaabaaada");

    strcpy(s[1].str,"bdaabaadaacbdbcaad");
    s[1].len = strlen("bdaabaadaacbdbcaad");
    
    ///////////////////abcddbcdbcbaaaabcccaabaaadaaaaabcbadabdaabaadaacbdbcaaddaaadabbaaddaadadbcbdacaaaadaadada"
    strcpy(t_out->str,"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

    
    BM_entrance(t,s,2,0,t_out);

    return 0;
}

*/