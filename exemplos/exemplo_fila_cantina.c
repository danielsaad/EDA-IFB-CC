#include <stdio.h>
#include <string.h>
#include "queue.h"
#include "alloc.h"


typedef struct aluno{
    char nome[30];
    int idade;
    double conta;
}aluno;


void* construtor_aluno(void* dado){
    aluno* ptr = mallocx(sizeof(aluno));
    memcpy(ptr,dado,sizeof(aluno));
    return ptr;
}

void destructor_aluno(void* data){
    free(data);
}


void le_aluno(aluno* a){
    printf("Nome: ");
    scanf("%s",a->nome);
    printf("Idade: ");
    scanf("%d",&(a->idade));
    printf("Conta: ");
    scanf("%lf",&(a->conta));
}

void insere_aluno(queue_t* q,aluno* a){
    queue_push(q,a);
}

void atende_aluno(queue_t* q){
    aluno a = *(aluno*) queue_front(q);
    printf("Atendendo aluno.\n");
    printf("Nome = %s\n",a.nome);
    printf("Idade = %d\n",a.idade);
    printf("Conta = %lf\n",a.conta);
    queue_pop(q);
}

int main(void){
    queue_t* fila;
    queue_initialize(&fila,construtor_aluno,destructor_aluno);
    while(1){
        int opcao;
        printf("Tia sandra, qual é a opção: ");
        scanf("%d",&opcao);
        if(opcao==1){
            aluno a;
            le_aluno(&a);
            insere_aluno(fila,&a);
        }
        else{
            atende_aluno(fila);
        }
    }
    return 0;
}
