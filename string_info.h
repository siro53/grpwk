#pragma once

typedef struct {
    char str[120];
    int len, id;
} string_s;

#define T_LENGTH 400001

typedef struct {
    char str[T_LENGTH + 1];
    int shift_var[T_LENGTH];
} string_out;
