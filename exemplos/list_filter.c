#include "list.h"
#include "alloc.h"
#include <stdio.h>
#include <string.h>

void imprime_lista(list_t *l) {
    list_iterator_t it = l->head;
    while (it != NULL) {
        int valor = *(int *)it->data;
        printf("%d->", valor);
        it = it->next;
    }
    printf("\n");
}

void *constructor_int(void *data) {
    void *ptr = mallocx(sizeof(int));
    memcpy(ptr, data, sizeof(int));
    return ptr;
}

void destructor_int(void *data) {
    free(data);
}

int is_zero(void *data) {
    int *z = data;
    if (*z == 0) {
        return 1;
    }
    return 0;
}

int is_one(void *data) {
    int *z = data;
    if (*z == 1) {
        return 1;
    }
    return 0;
}

void list_filter(list_t *l, int (*pred)(void *data)) {
    list_iterator_t it = l->head;
    list_iterator_t anterior = NULL;
    while (it != NULL) {
        if (!pred(it->data)) {
            if (it == l->head) {
                list_remove_head(l);
                it = l->head;
            } else {
                anterior->next = it->next;
                list_node_t *aux = it;
                it = it->next;
                l->destructor(aux->data);
                free(aux);
            }
        } else {
            anterior = it;
            it = it->next;
        }
    }
}

int main(void) {
    list_t *l;
    list_initialize(&l, constructor_int, destructor_int);
    int valor[8] = {1, 0, 3, 5, 0, 2, 0, 1};
    // int valor[1] = {1};
    for (int i = 0; i < 8; i++) {
        list_append(l, &valor[i]);
    }
    imprime_lista(l);
    list_filter(l, is_one);
    imprime_lista(l);
    return 0;
}