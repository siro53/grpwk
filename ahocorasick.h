#define AHO_TYPE int

typedef struct _n {
    AHO_TYPE data;
    struct _n *l, *r;
    int N;
} aho;

aho *aho_nullitem;
AHO_TYPE aho_nulldata;

void aho_init(void);
int aho_count(void);
void aho_insert(AHO_TYPE);
aho *aho_search(AHO_TYPE);
void aho_show_data(void (*func)(AHO_TYPE));
void aho_show_tree(void (*func)(AHO_TYPE));
