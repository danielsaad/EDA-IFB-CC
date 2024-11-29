#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include <stdbool.h>
#include <stdlib.h>

typedef struct stack_t {
    int* stack;
    size_t capacity;
    size_t size;
} stack_t;

void stack_initialize(stack_t **s);
void stack_delete(stack_t **s);
void stack_push(stack_t *s, int data);
int stack_top(stack_t *s);
void stack_pop(stack_t *s);
bool stack_empty(stack_t *s);
size_t stack_size(stack_t *s);

#endif