#include "list.h"
#include <stdio.h>
#include <string.h>

void print_list(list_t *l) {
    printf("\n");
    list_node_t *aux;
    for (aux = l->head; aux != NULL; aux = aux->next) {
        printf("%d -> ", aux->data);
    }
    printf("NULL\n");
    printf("\n");
}

int main() {
    list_t *l;
    list_initialize(&l);
    int i;
    for (i = 0; i < 3; i++) {
        list_append(l, i);
    }
    print_list(l);
    list_insert(l, 5, 1);
    print_list(l);
    list_remove_head(l);
    list_remove_tail(l);
    print_list(l);
    list_delete(&l);
    return 0;
}
