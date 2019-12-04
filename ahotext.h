#pragma once

typedef struct _text {
    int id;
    char *data;
    int len;
    struct _text *prev, *next;
} aho_text;

aho_text *text_init(const int id, char *data, const int len);
