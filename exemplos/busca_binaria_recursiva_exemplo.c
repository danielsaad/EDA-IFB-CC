#include <stdio.h>

int busca_binaria(int* v,int l,int r,int chave){
    if(l>r){
        return -1;
    }
    int m = (l+r)/2;
    if(chave==v[m]){
        return m;
    }
    else if(chave<v[m]){
        return busca_binaria(v,l,m-1,chave);
    }
    else{
        return busca_binaria(v,m+1,r,chave);
    }
}

int main(void){
    int chave = 11;
    int v[9] = {0,2,4,5,7,8,9,11,13};
    int pos = busca_binaria(v,0,8,chave);
    if(pos==-1){
        printf("Chave %d não ocorre no vetor.\n",chave);
    }
    else{
        printf("Chave %d ocorre na posição %d.\n",chave,pos);
    }
    return 0;
}
