#include <stdio.h>
#include <string.h>
#include "string_s.h"

// change here to include your files!!
#include "example/grpwk.h"

int main_prg(int argc, char *argv[]) {
    FILE *fp = fopen("data/dat0_in", "r");
    string_s t, s[50000];

    // input t
    fscanf(fp, "%s", t.str);
    t.len = strlen(t.str);

    // input s[]
    int i = 0;
    while (~fscanf(fp, "%s", s[i].str)) s[i++].len = strlen(s[i].str);

    grpwk(t, s, i);

    return 0;
}

int main(int argc, char *argv[]) {
    main_prg(argc, argv);

    return 0;
}
