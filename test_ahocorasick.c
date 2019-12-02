#include <stdio.h>
#include <string.h>

#include "ahocorasick.h"

int test_trie(void) {
    char *s[] = {
        "ab",
        "abc",
        "aaaaabddbdaaacccaacbaabacbaadb",
        "aaacdbdbcbcdbdbadaacbaadbdbdaacaaaaaadacababdadddacaacbaaaabdacdadadbabbbddaaddaaaaa",
        "abacbadaadbcaaabaaacbbaabadbababdbcadbd",
        "dbbbdaabaaabaabab",
        "daaadaaa",
        "dbaac",
        "ad",
        "bdadaabbaaadaabdd",
        "ddaabdd",
        "bdbabb",
        "abdb",
        "adbab",
        "aaabaaabcadba",
    };
    aho_text text[sizeof(s)/sizeof(s[0])];
    for (int i=0; i<sizeof(s)/sizeof(s[0]); i++) {
        text[i] = *text_init(i, s[i], strlen(s[i]));
    }

    aho_trie *t;
    trie_init(t);

    for (int i=0; i<sizeof(text)/sizeof(text[0]); i++) {
        if (!trie_add(t, &text[i])) printf("error (unexpected input [^a-d]\n");
    }
    trie_print(t);
    trie_connect(t);

    trie_print(t);

    return 0;
}

// outcome functions for testing
void callback_match_pos(void *arg, aho_match_t *m) {
    char *text = (char *)arg;

    printf("match text(%p): ", m);
    for (int i=m->pos; i<m->pos+m->len; i++) printf("%c", text[i]);

    printf(" (match id: %d position: %d length: %d)\n", m->id, m->pos, m->len);
}

int test_ahocora(void) {
    ahocorasick aho;
    aho_init(&aho);

    aho_add_match_text(&aho, "ab", strlen("ab"));
    aho_add_match_text(&aho, "abc", strlen("abc"));
    aho_add_match_text(&aho, "aaaaabddbdaaacccaacbaabacbaadb", strlen("aaaaabddbdaaacccaacbaabacbaadb"));
    aho_add_match_text(&aho, "aaacdbdbcbcdbdbadaacbaadbdbdaacaaaaaadacababdadddacaacbaaaabdacdadadbabbbddaaddaaaaa", strlen("aaacdbdbcbcdbdbadaacbaadbdbdaacaaaaaadacababdadddacaacbaaaabdacdadadbabbbddaaddaaaaa"));
    aho_add_match_text(&aho, "abacbadaadbcaaabaaacbbaabadbababdbcadbd", strlen("abacbadaadbcaaabaaacbbaabadbababdbcadbd"));
    aho_add_match_text(&aho, "dbbbdaabaaabaabab", strlen("dbbbdaabaaabaabab"));
    aho_add_match_text(&aho, "daaadaaa", strlen("daaadaaa"));
    aho_add_match_text(&aho, "dbaac", strlen("dbaac"));
    aho_add_match_text(&aho, "ad", strlen("ad"));
    aho_add_match_text(&aho, "bdadaabbaaadaabdd", strlen("bdadaabbaaadaabdd"));
    aho_add_match_text(&aho, "ddaabdd", strlen("ddaabdd"));
    aho_add_match_text(&aho, "bdbabb", strlen("bdbabb"));
    aho_add_match_text(&aho, "abdb", strlen("abdb"));
    aho_add_match_text(&aho, "adbab", strlen("adbab"));
    aho_add_match_text(&aho, "caabaaabcadba", strlen("aaabaaabcadba"));

    char test[] = "abcabcabcab";
    aho_create_trie(&aho);
    aho_register_match_callback(&aho, callback_match_pos, (void *)test);

    // trie_print(&aho.trie);

    printf("try: %s\n", test);
    printf("total match: %d\n", aho_search(&aho, test, strlen(test)));

    aho_destroy(&aho);

    return 0;
}

int main(void) {
    // test_trie();
    test_ahocora();

    return 0;
}
