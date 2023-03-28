#include <stdio.h>
#include <string.h>
#include "priority_queue.h"
#include "alloc.h"

typedef struct pessoa{
    char nome[30];
    int professor;
    char curso[30];
}pessoa;


void* construtor_pessoa(void* dado){
    pessoa* ptr = mallocx(sizeof(pessoa));
    memcpy(ptr,dado,sizeof(pessoa));
    return ptr;
}

void destructor_pessoa(void* data){
    free(data);
}

int comparator_pessoa(const void* a, const void* b){
    const pessoa *p1,*p2;
    p1 = a;
    p2 = b;
    if(p1->professor == p2->professor){
        return 0;
    }
    if(p1->professor){
        return 1;
    }
    return -1;

}


void le_pessoa(pessoa* p){
    printf("Nome: ");
    scanf("%s",p->nome);
    printf("É professor? (1 para sim 0 para não): ");
    scanf("%d",&(p->professor));
    printf("Curso: ");
    scanf("%s",p->curso);
}

void insere_pessoa(priority_queue_t* pq,pessoa* p){
    priority_queue_push(pq,p);
}

void atende_pessoa(priority_queue_t* pq){
    pessoa p = *(pessoa*) priority_queue_front(pq);
    printf("Atendendo pessoa.\n");
    printf("Nome = %s\n",p.nome);
    printf("Professor = %d\n",p.professor);
    printf("Curso = %s\n",p.curso);
    priority_queue_pop(pq);
}

int main(void){
    priority_queue_t* fila_de_prioridade;
    priority_queue_initialize(&fila_de_prioridade,
        construtor_pessoa,
        destructor_pessoa,
        comparator_pessoa);
    while(1){
        int opcao;
        printf("1) Inserir pessoa na fila.\n");
        printf("2) Atender uma pessoa.\n");
        printf("Tia sandra, qual é a opção: ");
        scanf("%d",&opcao);
        if(opcao==1){
            pessoa p;
            le_pessoa(&p);
            insere_pessoa(fila_de_prioridade,&p);
        }
        else{
            atende_pessoa(fila_de_prioridade);
        }
    }
    return 0;
}
