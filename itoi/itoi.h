#pragma once

#include "../string_info.h"
#include "../linked_list.h"

void ahocoralike(char *t, string_s s[], int from, int to, linked_list *t_opt, linked_list *s_count);

int s_opt_insert(linked_list *s_opt, int s_count, int index);
void discriminate(int s_id, int s_pos, string_s *text, linked_list *t_opt, linked_list *s_opt, linked_list *s_count);
