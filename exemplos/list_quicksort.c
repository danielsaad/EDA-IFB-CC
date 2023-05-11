#include "alloc.h"
#include "generic_list.h"
#include <stdio.h>
#include <string.h>
int menor_igual(const void *d1, const void *d2) {
    int a, b;
    a = *(int *)d1;
    b = *(int *)d2;
    return a <= b;
}

int maior(const void *d1, const void *d2) {
    int a, b;
    a = *(int *)d1;
    b = *(int *)d2;
    return a > b;
}

void cat(generic_list_t *l1, generic_list_t *l2) {
    while (!generic_list_empty(l2)) {
        generic_list_append(l1, generic_list_access_head(l2));
        generic_list_remove_head(l2);
    }
}

generic_list_t *list_copy(generic_list_t *l) {
    generic_list_iterator_t it;
    it = l->head;
    generic_list_t *l2;
    generic_list_initialize(&l2, l->constructor, l->destructor);
    while (it != NULL) {
        generic_list_append(l2, it->data);
        it = it->next;
    }
    return l2;
}
void imprime_lista(generic_list_t *l) {
    generic_list_iterator_t it = l->head;
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

void list_filter(generic_list_t *l,
                 int (*pred)(const void *data, const void *pivot)) {
    generic_list_iterator_t it = l->head;
    generic_list_iterator_t anterior = NULL;
    while (it != NULL) {
        if (!pred(it->data, generic_list_access_tail(l))) {
            if (it == l->head) {
                generic_list_remove_head(l);
                it = l->head;
                anterior = NULL;
            } else {
                anterior->next = it->next;
                generic_list_node_t *aux = it;
                it = it->next;
                l->destructor(aux->data);
                free(aux);
                l->size--;
            }
        } else {
            anterior = it;
            it = it->next;
        }
    }
}

generic_list_t *quicksort(generic_list_t *l) {
    printf("L = ");
    imprime_lista(l);
    if (generic_list_size(l) > 1) {
        generic_list_t *l1;
        generic_list_t *l2;
        generic_list_t *l3;
        l1 = list_copy(l);
        l3 = list_copy(l);
        generic_list_initialize(&l2, l->constructor, l->destructor);
        list_filter(l1, menor_igual);
        generic_list_append(l2, generic_list_access_tail(l1));
        generic_list_remove_tail(l1);
        list_filter(l3, maior);
        printf("L1 = ");
        imprime_lista(l1);
        printf("Pivo = ");
        imprime_lista(l2);
        printf("L3 = ");
        imprime_lista(l3);
        l1 = quicksort(l1);
        l3 = quicksort(l3);
        cat(l1, l2);
        cat(l1, l3);
        generic_list_delete(&l2);
        generic_list_delete(&l3);
        l2 = l;
        l = l1;
        generic_list_delete(&l2);
    }
    printf("Retornando: ");
    imprime_lista(l);
    return l;
}

int main(void) {
    generic_list_t *l;
    generic_list_initialize(&l, constructor_int, destructor_int);
    int valor[8] = {1, 0, 3, 5, 0, 2, 0, 1};
    for (int i = 0; i < 8; i++) {
        generic_list_append(l, &valor[i]);
    }
    imprime_lista(l);
    generic_list_t *l_final = quicksort(l);
    imprime_lista(l_final);
    return 0;
}