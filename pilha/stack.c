#include "stack.h"
#include "../utils/alloc.h"

void stack_initialize(stack_t **stack) {
    *stack = mallocx(sizeof(stack_t));
    dynamic_array_initialize(&(*stack)->stack_array);
}

void stack_delete(stack_t **stack) {
    dynamic_array_delete(&(*stack)->stack_array);
    free(*stack);
    *stack = NULL;
}

void stack_push(stack_t *stack, int data) {
    dynamic_array_push_back(stack->stack_array, data);
}

int stack_top(stack_t *stack) {
    return dynamic_array_back(stack->stack_array);
}

void stack_pop(stack_t *stack) {
    dynamic_array_pop_back(stack->stack_array);
}

bool stack_empty(stack_t *stack) {
    return stack_size(stack) == 0;
}

size_t stack_size(stack_t *stack) {
    return dynamic_array_size(stack->stack_array);
}
