#include <stdio.h>
#include <stdlib.h>

#include "grpwk.h"

char *grpwk(char *t, string_s s[], int len) {
    char *str = (char *)malloc(sizeof(char) * 100);
    sprintf(str, "I got %d data!", len);

    return str;
}