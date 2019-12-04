#include <stdio.h>
#include <stdlib.h>

#include "grpwk.h"

char *grpwk(const char *t, const string_s s[], int len) {
    char *str = (char *)malloc(sizeof(char) * 100);
    sprintf(str, "I got %d data!", len);

    return str;
}