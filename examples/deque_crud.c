#include "alloc.h"
#include "deque.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    int i;
    deque_t *d;
    deque_initialize(&d);
    for (i = 0; i < 16; i++) {
        if (i % 2 == 0) {
            printf("Inserindo %d na frente do deque\n", i);
            deque_push_front(d, i);
        } else {
            printf("Inserindo %d atras do deque\n", i);
            deque_push_back(d, i);
        }
    }
    i =0;
    while (!deque_empty(d)) {
        if (i % 2 == 1) {
            printf("Retirando %d da frente do deque\n", deque_front(d));
            deque_pop_front(d);
        } else {
            printf("Retirando %d de tras do deque\n", deque_back(d));
            deque_pop_back(d);
        }
        i++;
    }
    deque_delete(&d);
    return 0;
}
