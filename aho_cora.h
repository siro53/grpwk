#define AHO_TYPE int

typedef struct _n {
    AHO_TYPE data;
    struct _n *l, *r;
    int N;
} aho;

AHO_TYPE aho_nullitem;

void aho_init(void);
// int aho_count(void);
void aho_insert(AHO_TYPE);
// aho aho_search(AHO_TYPE);
// void aho_delete(AHO_TYPE);
// void aho_sort(void);
void aho_show(void);