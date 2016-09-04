#include <stdio.h>

int busca_binaria(int* v,int n,int chave){
    int l,r,m;
    l = 0;
    r = n-1;
    while(l<=r){
        m = (l+r)/2;
        if(chave<v[m]){
            r = m-1;
        }
        else if(chave>v[m]){
            l = m+1;
        }
        else{
            return m;
        }
    }
    return -1;
}

int main(void){
    int chave = 3;
    int v[9] = {0,2,4,5,7,8,9,11,13};
    int pos = busca_binaria(v,9,chave);
    printf("Chave %d ocorre na posição %d.\n",chave,pos);
}
