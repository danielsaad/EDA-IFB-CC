/**
 * Autor: Daniel Saad Nogueira Nunes
 * Comentários: Este programa aborda a correção do exemplo anterior.
 * A memória é liberada antes de trocarmos o valor do ponteiro.
 * Rode ele com o valgrind e compare a diferença de saída entre os dois.
 **/

#include <stdlib.h>
int main(void) {
    /* aloca-se um vetor de 100000 posições.*/
    int *ptr = malloc(sizeof(int) * 100000);
    /* libera-se a área de memória alocada */
    free(ptr);
    /* agora podemos mudar o valor de ptr */
    ptr = NULL;
    return 0;
}