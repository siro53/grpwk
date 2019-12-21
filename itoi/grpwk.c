#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../linked_list.h"
#include "grpwk.h"
#include "itoi.h"

// input_win.cから呼び出されるやつ
char *grpwk(char *t, string_s s[], int len) {
    char *ans = (char *)calloc(T_LENGTH + 1, sizeof(char));
    for (int i=0; i<T_LENGTH; i++) ans[i] = t[i] != 'x' ? t[i] : 'a';

    int from, to;
    for (from = 0; from<len; ++from) if (s[from].len == AHO_FROM) break;
    for (to = from; to<len; to++) if (s[to].len == AHO_TO) break;
    printf("len: %d\n", to - from);

    linked_list *t_opt = (linked_list *)malloc(sizeof(linked_list) * T_LENGTH);
    for (int i=0; i<T_LENGTH; i++) linked_init(&t_opt[i]);
    linked_list s_count[len];
    memset(s_count, 0, sizeof(linked_list) * len);

    ahocoralike(ans, s, from, to, t_opt, s_count);

    printf("ahocora end\n");

    linked_list s_opt[100];
    memset(s_opt, 0, sizeof(linked_list) * 100);
    // s_opt init
    for (int i=from; i<to; i++) {
        s_opt_insert(s_opt, s_count[i].length, i);
    }

    while (1) {
        // get next s to insert into ans
        int s_id = -1;
        if (s_opt[1].length != 0) s_id = linked_pop_int(&s_opt[1], 0);
        else for (int i=2; i<100; i++) {
            if (s_opt[i].length != 0) {
                s_id = linked_pop_int(&s_opt[i], 0);
                printf("i = %d, ", i);
                break;
            }
        }
        if (s_id == -1) break; // no option found
        printf("id: %d\n", s_id);
        if (s_count[s_id].length == 0) continue; // option already taken

        /* delete all other s that overlaps with the option */
        // option's text and place: index of first letter within t
        string_s *text = &s[s_id];
        int s_pos = linked_pop_int(&s_count[s_id], 0);
        // TODO: maybe better way to select the index above
        linked_destroy(&s_count[s_id]);

        // discriminate other options within the substituted places
        for (int t_index=0; t_index<text->len; t_index++) {
            while (t_opt[t_index + s_pos].length != 0) {
                // the other option
                linked_node *other = linked_pop_node(&t_opt[t_index + s_pos], 0);
                if (other->data == s_id || s_count[other->data].length == 0) { // same as the insert option
                    free(other);
                    continue;
                }

                printf("(%d %d) ", other->data, other->place);
                // go to s_count[other.id] and delete the option to insert here
                if (linked_delete_int(&s_count[other->data], t_index + s_pos - other->place)) {
                    // reinsert the deleted option to s_opt
                    s_opt_insert(s_opt, s_count[other->data].length, other->data);
                }
                free(other);
            }
        }
        printf("\n");
        sleep(1);

        /* insert text to ans */
        for (int i=0; i<text->len; i++) {
            ans[s_pos + i] = text->str[i];
        }
    }

    for (int i=0; i<100; i++) linked_destroy(&s_opt[i]);
    for (int i=0; i<T_LENGTH; i++) linked_destroy(&t_opt[i]);
    free(t_opt);

    return ans;
}
