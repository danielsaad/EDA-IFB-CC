/**
 * Autor: Daniel Saad Nogueira Nunes
 * Comentários: Neste programa é explorada
 * a emulação de passagem por referência em funções na
 * linguagem C.
**/

#include <stdio.h>

/* Em C, podemos emular uma passagem por referência através de
 * ponteiros.
 * Neste caso, uma cópia do ponteiro que aponta para o endereço de x
 * é criada. Como a cópia aponta para o endereço de x, podemos modificar 
 * o conteúdo da região de memória apontada por x. **/
 
void cubo(double *x){
	*x = *x * *x * *x;
}

int main(void){
    double a = 3;
    printf("O cubo de %f é ",a);
    cubo(&a);
    printf("%f\n",a);
	return(0);
}
