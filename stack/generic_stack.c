#include <stdlib.h>
#include <assert.h>
#include "generic_stack.h"
#include "../utils/alloc.h"

/**Inicializa pilha**/
void generic_stack_initialize(generic_stack_t** s,generic_stack_node_constructor_fn constructor,
                      generic_stack_node_destructor_fn destructor){
    (*s) = mallocx(sizeof(generic_stack_t));
    (*s)->size = 0;
    (*s)->top = NULL;
    (*s)->constructor = constructor;
    (*s)->destructor = destructor;
}

/**Destroi pilha**/
void generic_stack_delete(generic_stack_t** s){
    while(!generic_stack_empty(*s)){
        generic_stack_pop(*s);
    }
    free(*s);
    (*s) = NULL;
}



/**Retira o elemento do topo da pilha**/
void generic_stack_pop(generic_stack_t* s){
    assert(!generic_stack_empty(s));
    generic_stack_iterator_t it = s->top;
    s->top = s->top->next;
    s->destructor(it->data);
    free(it);
    s->size--;
}

/**Insere o elemento no topo da pilha**/
void generic_stack_push(generic_stack_t* s,void* data){
    generic_stack_node_t* new_node = mallocx(sizeof(generic_stack_node_t));
    new_node->data = s->constructor(data);
    new_node->next = s->top;
    s->top = new_node;
    s->size++;
}

/**Retorna o topo da pilha**/
void* generic_stack_top(generic_stack_t* s){
    assert(!generic_stack_empty(s));
    return(s->top->data);
}

/**Retorna o tamanho da pilha**/
size_t generic_stack_size(generic_stack_t* s){
    return(s->size);
}

/**Retorna se a pilha está vazia ou não**/
size_t generic_stack_empty(generic_stack_t* s){
    return(s->size==0 ? 1 : 0);
}
