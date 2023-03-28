#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void){
    int n;
    int j;
    srand(time(NULL));
    printf("Digite o tamanho do vetor a ser alocado: ");
    scanf("%d",&n);
    /* Aloca espaço para o vetor e inicializa com zero */
    int* v = calloc(n,sizeof(int));
    if(v==NULL){
        printf("Erro na alocação.\n");
        exit(EXIT_FAILURE);
    }
    /* O vetor é preenchido com números aleatórios.
     * Repare que o acesso á qualquer posição é feito através
     * do operador [], como se fosse um vetor normal.
     * De fato o que é feito é uma aritmética de ponteiros.
     * v[i] = *(v+i) */
    for(j=0;j<n;j++){
        v[j] = rand() % 1000; /** Gera um numero aleatório entre 0 e 999 **/
    }
    /* Impressão do vetor */
    for(j=0;j<n;j++){
        printf("v[%d] = %d\n",j,v[j]);
    }
    /* O vetor é liberado */
    free(v);
    return 0;
}
