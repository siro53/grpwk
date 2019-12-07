//
// Created by world on 2019/12/07.
//
#include <stdlib.h>
#include <stdio.h>
#include "../string_info.h"
#include "grpwk.h"

/*
char *t:入力文字列
string_s *s:入力文字列断片
int s_size:s_iの要素数
int s_id:処理していないs_iのうち、最も番号の若いもの
string_out *t_out:出力文字列の構造体
*/

void dosomething(char *t, string_s *s, int s_size, int s_id, string_out * t_out);

void template_entrance(char *t, string_s *s, int s_size, int s_id, string_out * t_out) {
    dosomething(t, s, s_size, s_id, t_out);
}

void template_exit(char *t, string_s *s, int s_size, int s_id, string_out * t_out) {
    //nextAlgorithm_template_entrance();
}

void dosomething(char *t, string_s *s, int s_size, int s_id, string_out * t_out) {

    int i = 0;
    for (i = 0; t_out->str[i] != '\0'; i++)
        if (t_out->str[i] == 'x')t_out->str[i] = 'a';

    template_exit(t, s, s_size, s_id, t_out);
}