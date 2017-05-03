#include <stdio.h>
#include <stdlib.h>


int** cria_matriz(int n){
	int** matriz;
	int i;
	matriz = malloc(sizeof(int*)*n);
	matriz[0] = malloc(sizeof(int)*n*n);
	for(i=1;i<n;i++){
		matriz[i] = matriz[i-1] + n;
	}
	return matriz;
}

void le_matriz(int** matriz, int n){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("m[%d][%d] = ",i,j);
			scanf("%d",&matriz[i][j]);
		}
	}
}

void imprime_matriz(int** matriz, int n){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%d ",matriz[i][j]);
		}
		printf("\n");
	}
}

int nro_de_estradas_chegam(int** m,int n,int k){
	int contador = 0;
	int i;
	for(i=0;i<n;i++){
		if(m[i][k])
			contador++;
	}
	return contador;
}

int nro_de_estradas_saem(int** m,int n,int k){
	int contador = 0;
	int i;
	for(i=0;i<n;i++){
		if(m[k][i])
			contador++;
	}
	return contador;
}

void exercicio_a (int** m, int n,int k){
	printf("%d estradas chegam na cidade %d\n",nro_de_estradas_chegam(m,n,k),k);
	printf("%d estradas saem da cidade %d\n",nro_de_estradas_saem(m,n,k),k);
}

void exercicio_b(int** m,int n){
	int i;
	int maior = -1;
	int id_maior = -1;
	for(i=0;i<n;i++){
		int aux  = nro_de_estradas_chegam(m,n,i) ;
		if(aux>maior){
			maior = aux;
			id_maior = i; 
		}
	}
	printf("Cidade que chegam mais estradas é a cidade %d, com total de %d estradas\n",id_maior,maior);
}

int verifica_isolada(int** m, int n, int k){
	int isolada = 1;
	int i;
	for(i=0;i<n;i++){
		if(m[i][k] || m[k][i]){
			isolada = 0;
		}
	}
	return isolada;
}

void exercicio_c(int**m, int n, int k ){
	int i;
	int cond = 1;
	for(i=0;i<n;i++){
		if(m[k][i]==1 && m[i][k]==0){
			cond = 0;
		}
	}
	if(cond){
		printf("Todas as estradas de %d são de mão dupla.\n",k);
	}
}

void exercicio_d(int** m,int n){
	int i;
	for(i=0;i<n;i++){
		if(verifica_isolada(m,n,i)){
			printf("A cidade %d é isolada!\n",i);
		}
	}
}


int main(void){
	int n;
	printf("Digite o tamanho da matriz: ");
	scanf("%d",&n);
	int **m = cria_matriz(n);
	le_matriz(m,n);
	imprime_matriz(m,n);
	exercicio_a(m,n,3);
	exercicio_b(m,n);
	exercicio_c(m,n,3);
	exercicio_c(m,n,1);
	exercicio_d(m,n);	
	return 0;
}