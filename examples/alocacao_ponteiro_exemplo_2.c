#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    scanf("%d", &n);
    int *ptr = calloc(n, sizeof(int));
    if (ptr == NULL) {
        printf("Erro de alocação.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++)
        ptr[i] = i;
    for (int i = 0; i < n; i++)
        printf("%d\n", ptr[i]);
    free(ptr);
    return 0;
}