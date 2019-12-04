#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grpwk.h"
#include "ahocora.h"

char *grpwk(const char *t, const string_s s[], int len) {
    int i = 0;
    for (; i<len && s[i].len > 40; ++i);
    const string_s *a = &s[i];

    char *ans = ahocoralike(t, a, len - i);
    return ans;
}
