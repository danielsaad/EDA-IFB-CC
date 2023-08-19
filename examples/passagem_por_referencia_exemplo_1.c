#include <stdio.h>

void troca(int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}

int main(void) {
    int a, b;
    a = 2;
    b = 3;
    troca(&a, &b);
    printf("a = %d b = %d\n", a, b);
    return 0;
}
