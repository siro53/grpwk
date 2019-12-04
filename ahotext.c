#include <stdlib.h>
#include <string.h>

#include "ahotext.h"

aho_text *text_init(const int id, char *data, const int len) {
    aho_text *text = (aho_text *)malloc(sizeof(aho_text));
    text->id = id;
    text->data = data;
    text->len = len;
    text->prev = NULL;
    text->next = NULL;
    return text;
}
