#pragma once

#define T_LENGTH 400001

typedef struct {
    char str[120];
    int len;
} string_s;


typedef struct {
    char str[T_LENGTH + 1];

    //shift_varには既に割り当てられたs_iがいるとき、t_outにおけるそのs_iの先端にあたる場所に、そこから何個右にずらせばt_outのs_iが割り当てられた場所に行けるかを示す値を入れる。つまり割り当て済s_iの長さ
    int shift_var[T_LENGTH];
} string_out;