#include <stdlib.h>
#include <string.h>

#include "grpwk.h"
#include "itoi.h"

void s_opt_insert(linked_list *s_opt, int s_count, string_s *s_i) {
    if (s_count < S_OPT_LEN) {
        if (s_i->len >= BM_TO) linked_unshift_int(&s_opt[s_count], s_i->id, 0);
        else linked_push_int(&s_opt[s_count], s_i->id, 0);
    }
}

/* delete all other s that overlaps with the option */
void eliminate(int t_index, linked_list *t_opt, linked_list *s_opt, linked_list *s_count, string_s *s) {
    // eliminate other options within the substituted places
    while (t_opt[t_index].length != 0) {
        // the other option
        linked_node *other = linked_pop_node(&t_opt[t_index], 0);
        if (s_count[other->data].length == 0) { // same as the insert option
            free(other);
            continue;
        }

        // go to s_count[other.id] and delete the option to insert here
        if (linked_delete_int(&s_count[other->data], t_index - other->place)) {
            // reinsert the deleted option to s_opt
            s_opt_insert(s_opt, s_count[other->data].length, &s[other->data]);
        }
        free(other);
    }
}