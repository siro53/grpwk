#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../constructions.h"
#include "grpwk.h"
#include "itoi.h"
#include "BM.h"
#include <unistd.h>

// input_win.cから呼び出されるやつ
char *grpwk(char *t, string_s *s, int len)
{
    /* 文字数の区切りを決定 */
    int bm_until, aho_until;
    for (bm_until = 0; bm_until < len; ++bm_until)
        if (s[bm_until].len <= BM_TO)
            break;
    for (aho_until = bm_until; aho_until < len; aho_until++)
        if (s[aho_until].len <= AHO_TO)
            break;

    /* BMはじめ */
    string_out *t_in = (string_out *)malloc(sizeof(string_out));
    string_out *t_out = (string_out *)malloc(sizeof(string_out));

    for (int i = 0; i < T_LENGTH; i++)
    {
        t_out->str[i] = 'x';
    }
    t_out->str[T_LENGTH] = '\0';
    ConstructTin(t_in, t);

    // init option lists
    linked_list *t_opt = (linked_list *)malloc(sizeof(linked_list) * T_LENGTH);
    for (int i = 0; i < T_LENGTH; i++)
        linked_init(&t_opt[i]);
    linked_list s_count[len];
    memset(s_count, 0, sizeof(linked_list) * len);
    ;
    BM(t_in, s, bm_until, t_out, s_count, t_opt);
    printf("bm done\n");

    // int err = 0;
    // for (int i = 0; i < T_LENGTH; i++)
    //     err += (t_in->str[i] != t_out->str[i] && t_in->str[i] != 'x' && t_out->str[i] != 'x' );
    // printf("err:%d\n",err);
    for (int i = 0; i < T_LENGTH; i++)
    {
        if (t_out->str[i] != 'x')
        {
            // if (t[i] != t_out->str[i])
            // {
            //     printf("error: %d\n", i);
            //     usleep(10000);
            // }
            t[i] = t_out->str[i];
        }
        else if (t[i] == 'x')
            t[i] = 'a';
    }
    // return t;

    ahocoralike(t, s, bm_until, aho_until, t_opt, s_count);
    printf("ahocora done\n");

    linked_list s_opt[100];
    memset(s_opt, 0, sizeof(linked_list) * 100);
    // s_opt init
    for (int i = 0; i < aho_until; i++)
    {
        s_opt_insert(s_opt, s_count[i].length, i);
    }

    /* delete options where t is already determined by BM */
    for (int i = 0; i < T_LENGTH; i++)
    {
        if (t_out->str[i] != 'x')
        {
            discriminate(i, t_opt, s_opt, s_count);
        }
    }
    printf("discrim done\n");

    /* TODO: test */
    // for (int i=0; i<aho_until; i++) {
    //     if (s_count[s[i].id].length) printf("%d: %d, %s(%d)\n", s[i].id, s_count[s[i].id].length, s[i].str, s[i].len);
    // }
    // for (int i=0; i<T_LENGTH; i++) {
    //     if (t_opt[i].length < 3) {
    //         printf("%d: ", i);
    //         linked_print(&t_opt[i]);
    //     }
    // }
    // linked_print(&s_opt[1]);

    while (1)
    {
        // get next s to insert into ans
        int s_id = -1;
        if (s_opt[1].length != 0)
            s_id = linked_pop_int(&s_opt[1], 0);
        else
            for (int i = 2; i < 4; i++)
            {
                if (s_opt[i].length != 0)
                {
                    s_id = linked_pop_int(&s_opt[i], 0);
                    break;
                }
            }
        if (s_id == -1)
            break; // no option found
        if (s_count[s_id].length == 0)
            continue; // option already taken
        // printf("id: %05d (%02d), opt: %d: %s\n", s_id, s[s_id].len, s_count[s_id].length, s[s_id].str);
        // usleep(1000);

        // option's text and place: index of first letter within t
        int s_pos = linked_pop_int(&s_count[s_id], 0);
        // TODO: maybe better way to select the index above
        linked_destroy(&s_count[s_id]);

        /* delete other options */
        string_s *text = &s[s_id];
        for (int i = 0; i < text->len; i++)
        {
            discriminate(s_pos + i, t_opt, s_opt, s_count);
        }

        /* insert text to ans */
        for (int i = 0; i < text->len; i++)
        {
            // if (t_out->str[s_pos + i] != 'x') printf("eorro\n");
            t_out->str[s_pos + i] = text->str[i];
        }
    }

    for (int i = 0; i < 100; i++)
        linked_destroy(&s_opt[i]);
    for (int i = 0; i < T_LENGTH; i++)
        linked_destroy(&t_opt[i]);
    free(t_opt);

    for (int i = 0; i < T_LENGTH; i++)
    {
        if (t_out->str[i] != 'x' && t_in->str[i] == 'x')
        {
            t[i] = t_out->str[i];
        }
    }

    free(t_in);
    free(t_out);
    return t;
}
