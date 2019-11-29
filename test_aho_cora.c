#include <stdio.h>
#include "aho_cora.h"

int main(void) {
    aho_init();
    aho_show();
    aho_insert(10);
    aho_insert(11);
    aho_insert(12);
    aho_insert(13);
    aho_insert(14);
    aho_insert(15);
    aho_insert(16);
    aho_show();
    return 0;
}