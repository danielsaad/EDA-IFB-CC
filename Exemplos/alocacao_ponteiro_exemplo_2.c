/**
 * Autor: Daniel Saad Nogueira Nunes
 * Comentários: Neste programa é explorada
 * a alocação dinâmica de structs através
 * de ponteiros em C.
**/


#include <stdlib.h>
#include "alloc.h"

typedef struct ExemploStruct{
	int a,b,c;
}ExemploStruct;

int main(void){
    ExemploStruct* estrutura_ptr;

    /* Aloca dinamicamente uma estrutura e passa o endereco inicial
     * da estrutura para o ponteiro */
    estrutura_ptr = mallocx(sizeof(ExemploStruct));
	
    /* O acesso em membros de estruturas apontadas por
     * ponteiros é feito através do operador seta.
     * Em resumo: (*estrutura_ptr).a é equivalente a
     * estrutura_ptr->a. Preferimos a segunda forma por ser
     * mais legível */
    estrutura_ptr->a=3;
    estrutura_ptr->b=4;
    estrutura_ptr->c=5;
				  
    /* Liberação do espaço alocado */
    free (estrutura_ptr);

	return(0);
	
}
