#include <stdlib.h>

/* Questão 1 */
double** aloca_matriz(int l,int c){
  double** m = malloc(sizeof(double*) * l);
  int i;
  for(i = 0; i<l;i++){
    m[i] = malloc(sizeof(double)*c);
  }
  return m;
}

/* Questão 2a */

void sem_saida(int** m,size_t n){
  int i,j;
  for(i=0;i<n;i++){
    int cond = 1; /* Verifica se a cidade não tem saída */
    for(j=0;j<n;j++){
      if(m[i][j])
       cond = 0;
    }
    if(cond){
      printf("%d nao tem saida",i);
    }
  }
}

/* Questão 2a */
void qtd_igual(int** m,size_t n){
  int i,j;
  for(i=0;i<n;i++){
    int cont_saida = 0;
    int cont_entrada = 0;
    for(j=0;j<n;j++){
      if(m[i][j]){
        cont_saida++;
      }
      if(m[j][i]){
        cont_entrada++;
      }
    }
    if(cont_saida==cont_entrada){
      printf("A cidade %d tem o mesmo número de entradas e saídas.",i);
    }
  }
}

/* Questão 3a */

void swap(int* v,size_t i,size_t j){
  int tmp = v[i];
  v[i] = v[j];
  v[j] = tmp;
}

void partition(int* v,int l,int r){
  int k = l-1;
  int pos = r;
  int i;
  for(i=l;i<r;i++){
    if(v[i]<v[r]){
      k++;
      swap(v,k,i);
    }
  }
  swap(v,r,k);
}

/* Questão 3b */

void insertionsort(int* v, size_t n){
  size_t i;
  for(i=1;i<n;i++){
    int ch = v[i];
    int j;
    for(j=i-1;j>=0 && ch<v[j];j--){
      v[j+1] = v[j];
    }
    v[j+1] = ch;
  }
}


/* Questão 4b */
int bsearch(int* v,size_t n,int k){
  int l = 0;
  int r = n-1;
  while(l<=r){
    int mid = (l+r)/2;
    if(k == v[mid]){
      return mid;
    }
    if(k<v[mid]){
      r = mid-1;
    }
    else{
      l = mid+1;
    }
  }
  return -1;
}
