#include <stdio.h>

int main(void) {
    int n;
    printf("Digite o valor de n: ");
    scanf("%d", &n);
    int v[n];
    for (int i = 0; i < n; i++)
        v[i] = i;
    for (int i = 0; i < n; i++)
        printf("%d\n", v[i]);
    return 0;
}