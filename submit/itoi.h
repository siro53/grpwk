#pragma once

#include "../string_info.h"
#include "../linked_list.h"

#define S_OPT_LEN 2

void ahocoralike(char *t, string_s s[], int from, int to, linked_list *t_opt, linked_list *s_count);

void s_opt_insert(linked_list *s_opt, int s_count, string_s *s_i);
void eliminate(int t_index, linked_list *t_opt, linked_list *s_opt, linked_list *s_count, string_s *s);
