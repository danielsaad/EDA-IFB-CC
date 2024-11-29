#include "stack.h"
#include "../utils/alloc.h"
#include <assert.h>

static void stack_expand(stack_t *s);
static void stack_shrink(stack_t *s);

void stack_initialize(stack_t **s) {
    *s = mallocx(sizeof(stack_t));
    (*s)->capacity = 4;
    (*s)->stack = mallocx(sizeof(int) * (*s)->capacity);
    (*s)->size = 0;
}

static void stack_expand(stack_t *s) {
    s->capacity *= 2;
    s->stack = reallocx(s->stack, sizeof(int) * s->capacity);
}

static void stack_shrink(stack_t *s) {
    s->capacity /= 2;
    s->stack = reallocx(s->stack, sizeof(int) * s->capacity);
}

void stack_delete(stack_t **s) {
    while (!stack_empty(*s)) {
        stack_pop(*s);
    }
    free((*s)->stack);
    free(*s);
    *s = NULL;
}

void stack_push(stack_t *s, int data) {
    if (s->size == s->capacity) {
        stack_expand(s);
    }
    s->stack[s->size++] = data;
}

int stack_top(stack_t *s) {
    assert(!stack_empty(s));
    return s->stack[s->size - 1];
}

void stack_pop(stack_t *s) {
    if (s->size == s->capacity / 4 && s->capacity > 4) {
        stack_shrink(s);
    }
    s->size--;
}

bool stack_empty(stack_t *s) {
    return stack_size(s) == 0;
}

size_t stack_size(stack_t *s) {
    return s->size;
}
