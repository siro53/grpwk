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

void convert(char *tmp, char *s, int len, unsigned long long bitchange) {
    for (int i=0; i<len; i++) {
        if (bitchange >> i & 1) tmp[i] = 'a';
        else tmp[i] = s[i];
    }
    tmp[len] = '\0';
}

char *ahocoralike(char *t, string_s s[], int len) {
    ahocorasick aho;
    aho_init(&aho);
    aho_create_trie(&aho);
    char tmp[120];

    for (int i=0; i<len; ++i) {
        aho_add_match_text(&aho, &s[i]);
        int max_bit = s[i].len / 2;
        unsigned long long until = ((unsigned long long)1<<s[i].len)-1;
        for (unsigned long long j=1; j<=until; j++) {
            if (bitcount(j) < max_bit) {
                convert(tmp, s[i].str, s[i].len, j);
                aho_add_similar_text(&aho, tmp, &s[i]);
            }
        }
    }

    aho_connect_trie(&aho);
    // trie_print(&aho.trie);

    char *ans = (char *)malloc(sizeof(char) * (T_LENGTH + 1));

    aho_register_match_callback(&aho, callback_match_pos, (void *)t);
    sprintf(ans, "total match: %d\n", aho_search(&aho, t, T_LENGTH));

    return ans;
}
