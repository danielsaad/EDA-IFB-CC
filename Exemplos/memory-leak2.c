/**
 * memory-leak2.c
 **/
#include <stdlib.h>
int main(void){

	int* ptr = malloc(sizeof(int)* 100000); /**aloca um vetor de 100000 posições.**/
    free (ptr); /**agora podemos mudar o valor de ptr**/
	ptr = NULL;
			 
	return(0);
}


