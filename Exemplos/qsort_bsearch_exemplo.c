/**
 * Autor: Daniel Saad Nogueira Nunes
 * Comentários: Neste programa realiza-se a ordenação de um vetor
 * de pessoas pelo CPF e busca-se neste vetor através de uma busca binária.
**/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoa{
    char nome[30];
    char cpf[20];
    int idade;
}pessoa;

/**
  Função de comparação de pessoas.
  Uma pessoa < outra se o cpf dela é
  menor que o da segunda.
**/
int compara_pessoa(const void* a, const void* b){
    const pessoa *p1,*p2;
    p1 = a;
    p2 = b;
    return(strcmp(p1->cpf,p2->cpf));
}


pessoa* cadastra_pessoas(int n){
    int i;
    pessoa* v = malloc(sizeof(pessoa)*n);
    if(v==NULL){
        printf("Erro de alocação.\n");
        exit(EXIT_FAILURE);
    }
    for(i=0;i<n;i++){
        printf("Nome: ");
        scanf("%s",v[i].nome);
        printf("CPF: ");
        scanf("%s",v[i].cpf);
        printf("Idade: ");
        scanf("%d",&v[i].idade);
    }
    return v;
}

void imprime_pessoa(pessoa p){
    printf("Nome: %s\n",p.nome);
    printf("CPF: %s\n",p.cpf);
    printf("Idade: %d\n",p.idade);
}

int main(void){
    int n;
    int i;
    printf("Quantas pessoas deseja cadastrar: ");
    scanf("%d",&n);
    pessoa* p = cadastra_pessoas(n);
    qsort(p,n,sizeof(pessoa),compara_pessoa);
    printf("***\n\n\nPessoas cadastradas***\n\n\n");
    for(i=0;i<n;i++){
        imprime_pessoa(p[i]);
    }
    printf("\n\n\n");
    while(1){
        pessoa k;
        printf("Digite o cpf para procurar uma pessoa ou digite 'sair': ");
        scanf("%s",k.cpf);
        if(strcmp(k.cpf,"sair")==0){
            break;
        }
        pessoa *pessoa_ptr = bsearch(&k,p,n,sizeof(pessoa),compara_pessoa);
        if(pessoa_ptr==NULL){
            printf("Pessoa inexistente na base de dados.\n");
        }
        else{
            printf("Pessoa encontrada.\n");
            imprime_pessoa(*pessoa_ptr);
        }
    }
    free(p);
    return 0;
}
