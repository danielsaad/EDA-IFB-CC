/**
 * Autor: Daniel Saad Nogueira Nunes
 * Comentários: Neste programa é explorada
 * a emulação de passagem por referência em funções na
 * linguagem C.
 **/
#include <stdio.h>

/* Em C, vetores sempre são passados por referência. Pois um vetor nada
 * nada mais é do que um nome para uma posição de memória. Um ponteiro
 * constante! */

void soma(int *x, int n) {
    int i;
    for (i = 0; i < n; i++)
        x[i]++;
}

int main(void) {
    int i;
    int x[] = {1, 2, 3, 4, 5, 6};
    int n = 6;
    printf("Vetor original: ");
    for (i = 0; i < n; i++)
        printf("%d ", x[i]);
    printf("\n");

    soma(x, 6);

    printf("Vetor modificado: ");
    for (i = 0; i < n; i++)
        printf("%d ", x[i]);
    printf("\n");
    return (0);
}
