/**
 * Autor: Daniel Saad Nogueira Nunes
 * Comentários: Neste programa é ilustrado o fato
 * de que vetores podem ser vistos como ponteiros,
 * e vice-versa através da aritmética de ponteiros
 **/

#include <stdio.h>

int main(void) {
    char s[] = {'a', 'b', 'r', 'a', '\0'};
    int v[] = {0, 1, 2, 3};
    char *ptr_s = s;
    int *ptr_v = v;
    size_t i;
    for (i = 0; i < 4; i++) {
        printf("Endereço de s[%zu] = %p.\n", i, &s[i]);
        printf("Endereço de v[%zu] = %p.\n", i, &v[i]);
    }
    for (i = 0; i < 4; i++) {
        printf("ptr_s + %zu = %p.\n", i, ptr_s + i);
        printf("ptr_v + %zu = %p.\n", i, ptr_v + i);
    }
    return 0;
}
