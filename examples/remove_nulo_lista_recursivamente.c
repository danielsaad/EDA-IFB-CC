#include "alloc.h"
#include "generic_list.h"
#include <stdio.h>
#include <string.h>

void *construtor_int(void *data) {
    void *ptr = mallocx(sizeof(int));
    memcpy(ptr, data, sizeof(int));
    return ptr;
}

void destrutor_int(void *data) {
    free(data);
}

generic_list_node_t *deleta_recursivo_nulos(generic_list_t *lista,
                                            generic_list_node_t *node) {
    if (node == NULL) {
        return NULL;
    }
    generic_list_node_t *aux = node->next;
    if (*(int *)node->data == 0) {
        lista->destructor(node->data);
        free(node);
        lista->size--;
        return deleta_recursivo_nulos(lista, aux);
    } else {
        node->next = deleta_recursivo_nulos(lista, aux);
        return node;
    }
}

void deleta_nulos(generic_list_t *lista) {
    lista->head = deleta_recursivo_nulos(lista, lista->head);
}

void imprime_lista(generic_list_t *lista) {
    generic_list_node_t *ptr = lista->head;
    while (ptr != NULL) {
        printf("%d->", *(int *)ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}
int main(void) {
    generic_list_t *lista;
    generic_list_initialize(&lista, construtor_int, destrutor_int);
    int i;
    int v[7] = {1, 0, 0, 0, 1, 2, 0};
    for (i = 0; i < 7; i++) {
        generic_list_append(lista, &v[i]);
    }
    imprime_lista(lista);
    deleta_nulos(lista);
    imprime_lista(lista);
    generic_list_delete(&lista);
    return 0;
}