#include "stack.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    stack_t *stack;
    stack_initialize(&stack);
    for (int i = 0; i < 1000000; i++) {
        stack_push(stack, i);
    }
    while (!stack_empty(stack)) {
        printf("%d\n", stack_top(stack));
        stack_pop(stack);
    }
    stack_delete(&stack);
    return 0;
}
