#include "alloc.h"
#include "queue.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    int i;
    queue_t *q;
    queue_initialize(&q);
    for (i = 0; i < 16; i++) {
        printf("Inserindo %d\n", i);
        queue_push(q, i);
    }
    while (!queue_empty(q)) {
        printf("Retirando %d\n", queue_front(q));
        queue_pop(q);
    }
    queue_delete(&q);
    return 0;
}
