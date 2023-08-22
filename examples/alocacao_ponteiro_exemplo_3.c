#include <stdio.h>
#include <stdlib.h>

typedef struct ExemploStruct {
    int a, b, c;
} ExemploStruct;

int main(void) {
    ExemploStruct *ptr_estrutura;
    ptr_estrutura = malloc(sizeof(ExemploStruct));
    if (ptr_estrutura == NULL) {
        printf("Erro de alocação.\n");
        exit(EXIT_FAILURE);
    }
    ptr_estrutura->a = 3;
    ptr_estrutura->b = 4;
    ptr_estrutura->c = 5;
    free(ptr_estrutura);
    return (0);
}