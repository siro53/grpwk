#include <stdio.h>
#include <string.h>

#include "ahocorasick.h"

void callback_match_total(void *arg, aho_match *m) {
    int *match_total = (int *)arg;
    (*match_total)++;
}

void callback_match_pos(void *arg, aho_match *m) {
    char *text = (char *)arg;

    printf("match text:");
    for (int i=m->pos; i <m->pos+m->len; i++) printf("%c", text[i]);

    printf("(match id: %d position: %llu length: %d)\n", m->id, m->pos, m->len);
}

int main(void) {
    ahocorasick aho;
    aho_init(&aho);

    int id[10] = {
        aho_add_match_text(&aho, "ab", 2);
        aho_add_match_text(&aho, "c", 1);
        aho_add_match_text(&aho, "a", 1);
        aho_add_match_text(&aho, "acd", 3);
    }, match_total = 0;

    aho_create_trie(&aho);
    aho_register_match_callback(&aho, callback_match_pos, &match_total);

    char test[] = "dabcacdfc";
    printf("try: %s\n", test);
    printf("total match: %d\n", aho_search(&aho, test, strlen(test)));

    aho_destroy(&aho);

    return 0;
}
