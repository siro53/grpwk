#define index_N 16

typedef struct Node *link;
struct Node{
    int *id;
    link b;
    int *x;
    int *count;
};
#define Min_len 14
#define ThreadNum 1

#define High(A, B) (A > B) ? A : B
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

#define idvar(A,B) (A - 'a')*4 + (B - 'a')
#define aa 0
#define ab 1
#define ac 2
#define ad 3
#define ba 4
#define bb 5
#define bc 6
#define bd 7
#define ca 8
#define cb 9
#define cc 10
#define cd 11
#define da 12
#define db 13
#define dc 14
#define dd 15

void writeTout(char* t_temp);
void template_entrance(string_out * t_in, string_s * s, int s_len, int now_id, string_out *t_out);
void BM_entrance(string_out * t_in, string_s * s, int s_len, int now_id, string_out *t_out, linked_list *s_count, linked_list *t_opt);
