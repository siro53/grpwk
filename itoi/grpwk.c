#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grpwk.h"
#include "../ahocorasick.h"

// outcome functions for testing
void callback_match_pos(void *arg, aho_match_t *m) {
    char *text = (char *)arg;

    // printf("match text: ");
    // for (int i=m->pos; i<m->pos+m->len; i++) printf("%c", text[i]);

    // printf(" (match id: %d position: %d length: %d)\n", m->id, m->pos, m->len);
}

char *ahocoralike(const char *t, const string_s s[], int len) {
    ahocorasick aho;
    aho_init(&aho);

    for (int i=0; i<len && s[i].len >= 10; ++i) {
        aho_add_match_text(&aho, s[i].str, s[i].len);
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

char *grpwk(const char *t, const string_s s[], int len) {
    int i = 0;
    for (; i<len; ++i) if (s[i].len <= 60) break;

    string_s *a = &s[i];
    char *ans = ahocoralike(t, a, len - i);
    return ans;
}
