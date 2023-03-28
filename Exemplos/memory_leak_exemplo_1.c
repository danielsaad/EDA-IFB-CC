/**
 * Autor: Daniel Saad Nogueira Nunes
 * Comentários: Este problema aborda uma péssima prática
 * de programação. Os vazamentos de memória (memory leaks).
 * Estes vazamentos consistem na perda da referência para uma
 * área alocada, tornando impossível acessar esta área novamente.
 * O consumo de memória é aumentado desnecessariamente e memory leaks
 * são muitas das vezes decorrência de um erro de lógia.
 * Para detectá-los, podemos usar a ferramenta valgrind.
 **/

#include <stdlib.h>
int main(void) {

    /* Aloca-se um etor de 100000 posições */
    int *ptr = malloc(sizeof(int) * 100000);
    /* MEMORY LEAK: atribui um novo endereço de memória para ptr
     * sem desalocar o bloco de memória alocado */
    ptr = NULL;
    return (0);
}