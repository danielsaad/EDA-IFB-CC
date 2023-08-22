#include <stdio.h>

int soma(int x[], int n) {
    int acc = 0;
    for (int i = 0; i < n; i++)
        acc += x[i];
    return acc;
}

int main(void) {
    int x[] = {1, 2, 3, 4, 5, 6};
    int res = soma(x, 6);
    printf("Resultado: %d\n", res);
    return 0;
}
