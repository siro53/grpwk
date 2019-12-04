#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grpwk.h"
#include "../ahocorasick.h"

// outcome functions for testing
void callback_match_pos(void *arg, aho_match_t *m) {
    char *text = (char *)arg;

    printf("match text: ");
    for (int i=m->pos; i<m->pos+m->len; i++) printf("%c", text[i]);

    printf(" (match id: %d position: %d length: %d)\n", m->id, m->pos, m->len);
}

char *grpwk(const string_s t, const string_s s[], int len) {
    char *ans = (char *)malloc(sizeof(char) * 100);

    ahocorasick aho;
    aho_init(&aho);

    aho_add_match_text(&aho, "ab", strlen("ab"));
    aho_add_match_text(&aho, "abc", strlen("abc"));
    aho_add_match_text(&aho, "ca", strlen("ca"));

    char test[] = "abcabcabcab";
    aho_create_trie(&aho);
    aho_register_match_callback(&aho, callback_match_pos, (void *)test);

    trie_print(&aho.trie);

    sprintf(ans, "total match: %d\n", aho_search(&aho, test, strlen(test)));

    aho_destroy(&aho);

    return ans;
}
