#include <stdio.h>
#include "aho_cora.h"

void print_int(AHO_TYPE a) {
    printf("(%d)", a);
}

int main(void) {
    aho_init();
    aho_insert(10);
    aho_insert(11);
    aho_insert(12);
    aho_insert(13);
    aho_insert(14);
    aho_insert(15);
    aho_insert(16);

    printf("N = %d\n", aho_count());
    aho_show_data(&print_int);
    aho_show_tree(&print_int);
    return 0;
}
