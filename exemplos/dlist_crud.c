#include "dlist.h"
#include <stdio.h>
#include <string.h>

void print_list(dlist_t *l) {
    printf("\n");
    dlist_node_t *aux;
    for (aux = l->head; aux != NULL; aux = aux->next) {
        printf("%d <-> ", aux->data);
    }
    printf("NULL\n");
    printf("\n");
}

int main() {
    dlist_t *l;
    dlist_initialize(&l);
    int i;
    for (i = 0; i < 3; i++) {
        dlist_append(l, i);
    }
    print_list(l);
    dlist_insert(l, 5, 1);
    print_list(l);
    dlist_remove_head(l);
    dlist_remove_tail(l);
    print_list(l);
    dlist_delete(&l);
    return 0;
}
