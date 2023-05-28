#include "generic_dlist.h"
#include "../utils/alloc.h"
#include <assert.h>

static generic_dlist_node_t *generic_dlist_new_node(void *data,
                                    generic_dlist_node_constructor_fn constructor);
static void generic_dlist_delete_node(generic_dlist_node_t *node,
                              generic_dlist_node_destructor_fn destructor);

static generic_dlist_node_t *generic_dlist_new_node(void *data,
                                    generic_dlist_node_constructor_fn constructor) {
    generic_dlist_node_t *new_node = mallocx(sizeof(generic_dlist_node_t));
    new_node->data = constructor(data);
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

static void generic_dlist_delete_node(generic_dlist_node_t *node,
                              generic_dlist_node_destructor_fn destructor) {
    destructor(node->data);
    free(node);
}

/**Inicializa a lista duplamente encadeada e seus membros**/
void generic_dlist_initialize(generic_dlist_t **l, generic_dlist_node_constructor_fn constructor,
                      generic_dlist_node_destructor_fn destructor) {
    (*l) = mallocx(sizeof(generic_dlist_t));
    (*l)->head = NULL;
    (*l)->tail = NULL;
    (*l)->size = 0;
    (*l)->constructor = constructor;
    (*l)->destructor = destructor;
}
/** Deleta a lista por inteiro e libera espaço em memória **/
void generic_dlist_delete(generic_dlist_t **l) {
    while (!generic_dlist_empty(*l)) {
        generic_dlist_remove_head(*l);
    }
    free(*l);
    *l = NULL;
}

void generic_dlist_insert(generic_dlist_t *l, void *data, size_t i) {
    assert(i <= generic_dlist_size(l));
    if (generic_dlist_empty(l) || i == 0) {
        generic_dlist_prepend(l, data);
    } else if (i == generic_dlist_size(l)) {
        /*Inserção na cauda*/
        generic_dlist_append(l, data);
    } else {
        generic_dlist_node_t *new_node = generic_dlist_new_node(data, l->constructor);
        /*Inserção no meio da lista*/
        /*Precisamos encontrar o elemento que antecede a posição i*/
        generic_dlist_iterator_t it = l->head;
        size_t k;
        for (k = 0; k < i - 1; k++) {
            it = it->next;
        }
        /*aux agora aponta pro elemento da posição i-1*/
        new_node->next = it->next;
        new_node->prev = it;
        it->next->prev = new_node;
        it->next = new_node;
        l->size++;
    }
}

/** Insere um elemento na cabeça da generic_dlista **/
void generic_dlist_prepend(generic_dlist_t *l, void *data) {
    generic_dlist_node_t *new_node = generic_dlist_new_node(data, l->constructor);
    if (generic_dlist_empty(l)) {
        l->tail = new_node;
    } else {
        l->head->prev = new_node;
    }
    new_node->next = l->head;
    l->head = new_node;
    l->size++;
}

/**Insere um elemento na cauda da generic_dlista **/
void generic_dlist_append(generic_dlist_t *l, void *data) {
    generic_dlist_node_t *new_node = generic_dlist_new_node(data, l->constructor);
    if (generic_dlist_empty(l)) {
        l->head = new_node;
    } else {
        l->tail->next = new_node;
    }
    new_node->prev = l->tail;
    l->tail = new_node;
    l->size++;
}

/**Remove o elemento da posição i da generic_dlista**/
void generic_dlist_remove(generic_dlist_t *l, size_t i) {
    assert(!generic_dlist_empty(l) && i < generic_dlist_size(l));
    generic_dlist_node_t *node;
    if (generic_dlist_size(l) == 1 || i == 0) {
        generic_dlist_remove_head(l);
    } else if (i == generic_dlist_size(l) - 1) {
        generic_dlist_remove_tail(l);
    } else {
        generic_dlist_iterator_t it = l->head;
        size_t k;
        for (k = 0; k < i; k++) {
            it = it->next;
        }
        node = it;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        generic_dlist_delete_node(node, l->destructor);
        l->size--;
    }
}

void generic_dlist_remove_head(generic_dlist_t *l) {
    assert(!generic_dlist_empty(l));
    generic_dlist_iterator_t node = l->head;
    l->head = l->head->next;
    if (generic_dlist_size(l) == 1) {
        l->tail = NULL;
    } else {
        l->head->prev = NULL;
    }
    generic_dlist_delete_node(node, l->destructor);
    l->size--;
}

void generic_dlist_remove_tail(generic_dlist_t *l) {
    assert(!generic_dlist_empty(l));
    generic_dlist_iterator_t node = l->tail;
    l->tail = l->tail->prev;
    if (generic_dlist_size(l) == 1) {
        l->head = NULL;
    } else {
        l->tail->next = NULL;
    }
    generic_dlist_delete_node(node, l->destructor);
    l->size--;
}

void *generic_dlist_access(generic_dlist_t *l, size_t i) {
    assert(!generic_dlist_empty(l) && i < generic_dlist_size(l));
    generic_dlist_iterator_t it = l->head;
    int j;
    for (j = 0; j < i; j++) {
        it = it->next;
    }
    return (it->data);
}

void *generic_dlist_access_head(generic_dlist_t *l) {
    assert(!(generic_dlist_empty(l)));
    return (l->head->data);
}

void *generic_dlist_access_tail(generic_dlist_t *l) {
    assert(!generic_dlist_empty(l));
    return (l->tail->data);
}

/**Retorna o tamanho da generic_dlista**/
size_t generic_dlist_size(generic_dlist_t *l) {
    return l->size;
}

/**Retorna verdadeiro se a generic_dlista está vazia, e falso caso contrário**/
size_t generic_dlist_empty(generic_dlist_t *l) {
    return generic_dlist_size(l) == 0 ? 1 : 0;
}
