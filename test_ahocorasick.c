#include <stdio.h>
#include <string.h>

#include "ahocorasick.h"

int test_trie(void) {
    char *s[] = {
        "abs",
        "abc",
        "hoge",
        "test",
    };
    aho_text text[sizeof(s)/sizeof(s[0])];
    for (int i=0; i<sizeof(s)/sizeof(s[0]); i++) {
        text[i] = *text_init(i, s[i], strlen(s[i]));
    }

    printf("here\n");

    aho_trie *t = NULL;
    trie_init(t);

    for (int i=0; i<sizeof(text)/sizeof(text[0]); i++) {
        trie_add(t, &text[i]);
    }
    trie_print(t);
    trie_connect(t);

    trie_print(t);

    return 0;
}

// outcome functions for testing
void callback_match_total(void *arg, aho_match *m) {
    int *match_total = (int *)arg;
    (*match_total)++;
}

void callback_match_pos(void *arg, aho_match *m) {
    char *text = (char *)arg;

    printf("match text:");
    for (int i=m->pos; i <m->pos+m->len; i++) printf("%c", text[i]);

    printf("(match id: %d position: %d length: %d)\n", m->id, m->pos, m->len);
}

int test_ahocora(void) {
    ahocorasick *aho = NULL;
    aho_init(aho);

    int id[10] = {
        aho_add_match_text(aho, "ab", 2),
        aho_add_match_text(aho, "c", 1),
        aho_add_match_text(aho, "a", 1),
        aho_add_match_text(aho, "acd", 3),
    }, match_total = 0;

    aho_create_trie(aho);
    aho_register_match_callback(aho, callback_match_pos, &match_total);

    char test[] = "dabcacdfc";
    printf("try: %s\n", test);
    printf("total match: %d\n", aho_search(aho, test, strlen(test)));

    aho_destroy(aho);

    return 0;
}

int main(void) {
    test_trie();
    // test_ahocora();

    return 0;
}
