#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grpwk.h"
#include "ahocora.h"

// input_win.cから呼び出されるやつ
char *grpwk(char *t, string_s s[], int len) {
    int from, to;
    for (from = 0; from<len; ++from) if (s[from].len == AHO_FROM) break;
    for (to = from; to<len; to++) if (s[to].len == AHO_TO) break;

    char *ans = ahocoralike(t, s + from, to - from);
    return ans;
}
