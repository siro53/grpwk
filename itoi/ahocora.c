#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ahocorasick.h"
#include "ahocora.h"

// outcome functions for testing
void callback_match_pos(void *arg, aho_match_t *m) {
    char *text = (char *)arg;

    if (m->len > 20) {
        printf("match text: ");
        for (int i=m->pos; i<m->pos+m->len; i++) printf("%c", text[i]);
        printf(" (match id: %d position: %d length: %d)\n", m->id, m->pos, m->len);
    }
}

int bitcount(unsigned long long bits) {
    bits = (bits & 0x5555555555555555) + (bits >> 1 & 0x5555555555555555);
    bits = (bits & 0x3333333333333333) + (bits >> 2 & 0x3333333333333333);
    bits = (bits & 0x0f0f0f0f0f0f0f0f) + (bits >> 4 & 0x0f0f0f0f0f0f0f0f);
    bits = (bits & 0x00ff00ff00ff00ff) + (bits >> 8 & 0x00ff00ff00ff00ff);
    bits = (bits & 0x0000ffff0000ffff) + (bits >> 16 & 0x0000ffff0000ffff);
    bits = (bits & 0x00000000ffffffff) + (bits >> 32 & 0x00000000ffffffff);
    return bits;
}

const char *convert(const char *s, const int len, const unsigned long long bitcheck) {
    char *tmp = (char *)malloc(sizeof(char) * (len + 1));
    for (int i=0; i<len; i++) {
        if (bitcheck & (1 << i)) tmp[i] = 'a';
        else tmp[i] = s[i];
    }
    tmp[len] = '\0';
    return tmp;
}

char *ahocoralike(const char *t, const string_s s[], const int len) {
    ahocorasick aho;
    aho_init(&aho);

    for (int i=0; i<len; ++i) {
        if (s[i].len < 10) break;
        for (unsigned long long j=0; j<=(unsigned long long)(1<<s[i].len)-1; j++) {
            if (bitcount(j) < s[i].len / 2)
                aho_add_match_text(&aho, convert(s[i].str, s[i].len, j), s[i].len);
        }
    }

    aho_create_trie(&aho);
    // trie_print(&aho.trie);

    char *ans = (char *)malloc(sizeof(char) * (T_LENGTH + 1));
    // printf("test case: %s\n", t);

    aho_register_match_callback(&aho, callback_match_pos, (void *)t);
    sprintf(ans, "total match: %d\n", aho_search(&aho, t, T_LENGTH));

    aho_destroy(&aho);

    return ans;
}
