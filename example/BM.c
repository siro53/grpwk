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


//文字の比較に使用　単に見栄えを良くしてるだけ
#define ignore -1
#define success 1
#define failure 0

//これより短いs_iは処理しない
#define Min_len 35

#define High(A,B) (A>B) ? A:B

void BM_main(string_out * t_in, string_s *s, int s_size, int s_id, string_out *t_out);
int BMcomp(char tc, char sc);
void Detect(string_s s_i, string_out *t_out, int detection_id);

void BM_entrance(string_out * t_in, string_s *s, int s_size, int s_id, string_out *t_out) {
    BM_main(t_in, s, s_size, s_id, t_out);
}

void BM_exit(string_out * t_in, string_s *s, int s_size, int s_id, string_out *t_out) {
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
    /*----------------------DebugPrint-------------------------*/
    //printf("\nShift s_i by %d\n\n",i);
    /*---------------------------------------------------------*/
    return i;
}

void makeHShiftTable(int htable[], string_s s_i){
    int i;
    for(i=0;i<4;i++)
        htable[i] = shift(i+'a',s_i,1);
}

void makeShiftTable(int table[][4], string_s s_i){
    int i,j;
    for(i=0;i<30;i++){
        for(j=0;j<4;j++){
            table[i][j] = shift((char)(j+'a'),s_i,i);
        }
    }
}

double shiftave=0;
int lensum=0;
int BM(string_out *t_in, string_s s_i, string_out *t_out) {
    //t_id:s_iの最後尾がいる場所 esc:一致した文字の個数 comp_var:何回比較したか
    int t_id = s_i.len - 1, esc = 0, comp_var = 0, point = t_id;
    int table[30][4];
    int shiftsum = 0,count=0;
    makeShiftTable(table,s_i);
    
    while(1/*t_id <= T_LENGTH*/){
        count++;
        //printf("sgf");
        int flag = 1;
        //s_xが検出済で既に挿入されている場合、挿入済箇所をスキップ
        /*----------------------DebugPrint-------------------------*/
        //printf("Whether or not already matched|character:%c\n",t_out->str[t_id]);
        /*---------------------------------------------------------*/
        if(t_out->str[t_id] != 'x'){
        
            /*----------------------DebugPrint-------------------------*/
            //printf("Caution|Already matched:Character is not 'x',shifts s_i position\n");
            //printf("out:%s\n",t_out->str);
            /*---------------------------------------------------------*/

            t_id += t_out->shift_var[t_id - s_i.len];
            point = t_id;
        }else{
            //printf("Did not match\n");
        }

        //s_iが指定位置t_idにマッチするか確認
        while((flag == 1) && (esc < 12) && (s_i.len - 1 - comp_var >= 0 ) && (t_id < strlen(t_in->str))){
            
            /*----------------------DebugPrint-------------------------*/
            /*---------------------------------------------------------*/
            /*
            printf("t_s:");
            int j;
            for(j=0;j<strlen(t_in->st1r);j++)
                printf("%d",t_in->shift_var[j]);
            printf("\nt  :%s\n",t_in->str);
            printf("s_i:");
            
            for(j=0;j<t_id-s_i.len+1;j++)
                printf(" ");
            printf("%s\n",s_i.str);
            printf("cmp:");
            for(j=0;j<t_id-comp_var;j++)
                printf(" ");
            printf("^\n");
            printf("t_id:%d  comp_var:%d\n",t_id,comp_var);
            /*---------------------------------------------------------*/
            /*---------------------------------------------------------*/
            switch (BMcomp(t_in->str[t_id - comp_var], s_i.str[s_i.len - 1 - comp_var])){
                case ignore:
                    comp_var+=t_in->shift_var[t_id - comp_var];
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
        if (flag == 1){

            /*----------------------DebugPrint-------------------------*/
            //printf("\nDetected the exact position of s_i len:%d ave:%.2f\n",s_i.len,(double)shiftsum/count);
            printf(" len:%d ",s_i.len);
            shiftave += (double)shiftsum/count;
            lensum += s_i.len;
            //printf("Test %s\n%s\n%d\n",s_i.str,t_out.str,t_id);
            //Detect(s_i, t_out, t_id);
            //printf("Before s_i assignment:%s\n",t_out->str);
            /*----------------------DebugPrint-------------------------*/

            int x,y;
            for (x = s_i.len - 1, y = 0; x >= 0; x--, y++){
                t_out->str[t_id - y ] = s_i.str[x];
                //printf("t_out:%s oc:%c sc:%c\n",t_out->str,t_out->str[t_id - y],s_i.str[x]);
            }
            t_out->shift_var[t_id - y ] = s_i.len;
            
            /*----------------------DebugPrint-------------------------*/

            //printf("After  s_i assignment:%s\n\n\n",t_out->str);
            /*----------------------DebugPrint-------------------------*/
            return 0 ;
        } else{
            int temp;

            if(comp_var<30)
                if((t_id - point + 1 < 30) && (t_in->str[point] - 'a' < 4) && (t_in->str[point] - 'a' >= 0) && (t_id - point + 1 >= 0))temp = High(table[t_id - point + 1][t_in->str[point] - 'a'] + 1,table[comp_var][t_in->str[t_id - comp_var] - 'a']);
                else temp = table[comp_var][t_in->str[t_id - comp_var] - 'a'];
            else temp = shift(t_in->str[t_id - comp_var], s_i, comp_var);
            shiftsum += temp;
                /*
            if(comp_var<30)
                temp = table[comp_var][t_in->str[t_id - comp_var] - 'a'];
            else temp = shift(t_in->str[t_id - comp_var], s_i, comp_var);
*/
            //printf("point:%c %c\n",t_in->str[point],t_in->str[t_id]);
            //printf("t_id:%d\n",t_id);
            t_id+=temp;
            comp_var = 0;
            point = t_id;
        }

    }
    
    printf("error: s_i did not match anywhere in T\n");
    return -1;


}

void makeBigramTable(string_out *t_in, char index[][3]){

}

void BM_main(string_out *t_in, string_s *s, int s_size, int s_id, string_out *t_out){
    int i,j=0;
    char index[16][3] = {"aa", "ab", "ac", "ad", "ba", "bb", "bc", "bd", "ca", "cb", "cc", "cd", "da", "db", "dc", "dd"};//[][0]:１文字目　[][1]:２文字目　[][2]:終端文字
    link head;
    string_s s_i;

    for(i = 0; s[s_id+i].len > Min_len ;i++){
        //if(i>5)break;
        s_i = s[s_id + i];
        int temp = BM(t_in,s_i,t_out);
        printf(" i:%d Save:%.2f Slen:%d\n",i,shiftave/i,lensum);
        if(temp == -1)
            printf("s_id:%d",s_id+i);
    }
    s_id += i;
    BM_exit(t_in,s,s_size,s_id,t_out);
    //printf("\nDetected s_i count:%d :%d\n",count[0],count[1]);
}

int main(void){
    unsigned long int start,end;
    start = clock();
    string_s *s;
    string_out Base ,*t_out ,inBase , *t_in;
    t_out = &Base;
    t_in = &inBase;
    s = malloc(sizeof(string_s) * 50000);
int n=1;

    char t[T_LENGTH];
    FILE *fp_in;
    char fname[] = "../data/dat4_in";
    fp_in = fopen(fname,"r");
    if(fp_in == NULL){
        printf("???");
    }

            // input t
    fscanf(fp_in, "%s", t);

            // input s[]
    int counter = 0;
    for (; fscanf(fp_in, "%s", s[counter].str) != EOF; ++counter) {s[counter].len = strlen(s[counter].str);  
    }


    //char t[] = "abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada";
    ///////////////////abcddbcdbcbaaaabcccaabaaadaaaaabcbadabdaabaadaacbdbcaaddaaadabbaaddaadadbcbdacaaaadaadada"
    //strcpy(t_out->str,"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    
    ConstructSMatrix(s,counter);
    ConstructTout(t_out, t);
    ConstructTin(t_in,t);

    BM_entrance(t_in,s,2,0,t_out);
    end = clock();

    printf("time:%lf\n",(double)(end-start)/CLOCKS_PER_SEC);
    
    return 0;
}

