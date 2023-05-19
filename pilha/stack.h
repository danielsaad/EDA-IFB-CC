#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "../vetor-dinamico/dynamic_array.h"
#include <stdbool.h>

typedef struct stack_t {
    dynamic_array *stack_array;
} stack_t;

void stack_initialize(stack_t **stack);
void stack_delete(stack_t **stack);
void stack_push(stack_t *stack, int data);
int stack_top(stack_t *stack);
void stack_pop(stack_t *stack);

bool stack_empty(stack_t *stack);
size_t stack_size(stack_t *stack);

#endif