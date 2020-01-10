#include "sunday.h"
#include <unistd.h>

void sunday_init(string_s *s, int length, int qsbs[][ASIZE]) {
    for (int i=0; i<length; i++) {
        for (int j=0; j<ASIZE; j++) qsbs[i][j] = s[i].len + 1;
        for (int j=0; j<s[i].len; j++) qsbs[i][s[i].str[j] - 'a'] = s[i].len - j;
    }
}

int is_same(char *a, char *b, int length) {
    for (int i=0; i<length; i++) {
        if (a[i] != b[i] && a[i] != 'x') return 0;
    }
    return 1;
}

int shift_num(char c, int qsbs[ASIZE]) {
    if (c == 'x') return 1;
    else return qsbs[c - 'a'];
}

void sunday(char *t, string_s *s, int length, linked_list *t_opt, linked_list *s_count) {
    int qsbs[length][ASIZE];
    sunday_init(s, length, qsbs);

    for (int i=0; i<length; i++) {
        // printf("s[%d]: %d ... ", i, s[i].len);
        int index = 0, counter = 0;
        while (index + s[i].len < T_LENGTH) {
            if (is_same(t + index, s[i].str, s[i].len)) {
                linked_push_int(&s_count[i], index, 0);
                for (int j=0; j<s[i].len; j++) {
                    linked_push_node(&t_opt[index + j], i, j, 0);
                }
                counter++;
            }
            // printf("%d %d\n", t[index + s[i].len], shift_num(t[index + s[i].len], qsbs[i]));
            index += shift_num(t[index + s[i].len], qsbs[i]);
        }
        // printf("%d\n", counter);
    }
}