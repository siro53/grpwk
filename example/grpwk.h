#pragma once

#include "../string_info.h"
#include "../linked_list.h"

char *grpwk(char* t, string_s * s, int len);
void writeTout(char* t_temp);
void template_entrance(string_out * t_in, string_s * s, int s_len, int now_id, string_out *t_out);
void BM_entrance(string_out * t_in, string_s * s, int s_len, int now_id, string_out *t_out, linked_list *s_count, linked_list *t_opt);
