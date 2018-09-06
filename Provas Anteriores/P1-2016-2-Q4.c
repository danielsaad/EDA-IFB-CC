#include <stdio.h>

int verifica_isolada(int** matriz,int n,int cidade){
	int k;
	for(k=0;k<n;k++){
		if(m[cidade][k]){
			return 0;
		}
	}	
	for(k=0;k<n;k++){
		if(m[k][cidade]){
			return 0;
		}
	}
	return 1;
}

int nro_cidades_chegam(int** matriz, int n, int cidade){
	int k;
	int soma = 0;
	for(k=0;k<n;k++){
		if(matriz[k][cidade]){
			soma++;
		}
	}
	return soma;
}
void imprime_chega_mais(int** matriz,int n){
	int cidade;
	int maximo = 0;
	int* contador = calloc(n,sizeof(int));
	for(cidade=0;cidade<n;cidade++){
	 	contador[cidade] = nro_cidades_chegam(matriz,n,cidade);
		if(contador[cidade]>maximo){
			maximo = contador[cidade];
		}
	}
	for(cidade=0;cidade<n;cidade++){
		if(contador[cidade]==maximo){
			printf("Cidade %d é uma das que mais saem estradas.\n",cidade);
		}
	}
	free(cidade);

}

void imprime_isoladas(int** matriz,int n){
	int cidade;
	for(cidade=0;cidade<n;cidade++){
		if(verifica_isolada(matriz,n,cidade)){
			printf("A cidade %d é isolado.\n",cidade);
		}
	}
}