#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "../utils/alloc.h"

/**Inicializa pilha**/
void stack_initialize(stack_t** s,stack_node_constructor_fn constructor,
                      stack_node_destructor_fn destructor){
    (*s) = mallocx(sizeof(stack_t));
    (*s)->size = 0;
    (*s)->top = NULL;
    (*s)->constructor = constructor;
    (*s)->destructor = destructor;
}

/**Destroi pilha**/
void stack_delete(stack_t** s){
    while(!stack_empty(*s)){
        stack_pop(*s);
    }
    free(*s);
    (*s) = NULL;
}



/**Retira o elemento do topo da pilha**/
void stack_pop(stack_t* s){
    assert(!stack_empty(s));
    stack_iterator_t it = s->top;
    s->top = s->top->next;
    s->destructor(it->data);
    free(it);
    s->size--;
}

/**Insere o elemento no topo da pilha**/
void stack_push(stack_t* s,void* data){
    stack_node_t* new_node = mallocx(sizeof(stack_node_t));
    new_node->data = s->constructor(data);
    new_node->next = s->top;
    s->top = new_node;
    s->size++;
}

/**Retorna o topo da pilha**/
void* stack_top(stack_t* s){
    assert(!stack_empty(s));
    return(s->top->data);
}

/**Retorna o tamanho da pilha**/
size_t stack_size(stack_t* s){
    return(s->size);
}

/**Retorna se a pilha está vazia ou não**/
size_t stack_empty(stack_t* s){
    return(s->size==0 ? 1 : 0);
}
