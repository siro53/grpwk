#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ahocorasick.h"
#include "ahocora.h"

// outcome functions for testing
void callback_match_pos(void *arg, aho_match_t *m) {
    char *text = (char *)arg;

    // for (int i=m->pos; i<m->pos+m->len; i++) printf("%c", text[i]);
    // printf(" (match id: %d position: %d length: %d)\n", m->id, m->pos, m->len);
}

int bitcount(unsigned long long bits) {
    bits = (bits & 0x5555555555555555) + (bits >> 1 & 0x5555555555555555);
    bits = (bits & 0x3333333333333333) + (bits >> 2 & 0x3333333333333333);
    bits = (bits & 0x0f0f0f0f0f0f0f0f) + (bits >> 4 & 0x0f0f0f0f0f0f0f0f);
    bits = (bits & 0x00ff00ff00ff00ff) + (bits >> 8 & 0x00ff00ff00ff00ff);
    bits = (bits & 0x0000ffff0000ffff) + (bits >> 16 & 0x0000ffff0000ffff);
    return (bits & 0x00000000ffffffff) + (bits >> 32 & 0x00000000ffffffff);
}

char *ahocoralike(const char *t, string_s s[], const int len) {
    ahocorasick aho;
    aho_init(&aho);
    aho_create_trie(&aho);

    char tmp[120];
    int pre_len = s[0].len;

    for (int i=0; i<len; ++i) {
        if (s[i].len != pre_len) {
            printf("%d\n", pre_len);
            pre_len = s[i].len;
        }
        aho_add_match_text(&aho, &s[i]);
        for (unsigned long long j=1; j<=((unsigned long long)1<<s[i].len)-1; j++) {
            if (bitcount(j) < s[i].len * 2 / 5.0) {
                for (int v=0; v<s[i].len; v++) {
                    if (j & ((unsigned long long)1 << v)) tmp[v] = 'a';
                    else tmp[v] = s[i].str[v];
                }
                tmp[s[i].len] = '\0';
                aho_add_similar_text(&aho, tmp, &s[i]);
            }
        }
    }

    aho_connect_trie(&aho);
    // trie_print(&aho.trie);

    char *ans = (char *)malloc(sizeof(char) * (T_LENGTH + 1));
    // printf("test case: %s\n", t);

    aho_register_match_callback(&aho, callback_match_pos, (void *)t);
    sprintf(ans, "total match: %d\n", aho_search(&aho, t, T_LENGTH));

    return ans;
}
