#include <string.h>
#include <stdio.h>
#include <time.h>
#include "alloc.h"
#include "priority_queue.h"


typedef struct aluno{
    char nome[50];
    double p1,p2,p3;
} aluno;

void* aluno_constructor(void* data){
    void* ptr = mallocx(sizeof(aluno));
    memcpy(ptr,data,sizeof(aluno));
    return ptr;
}

void aluno_destructor(void* data){
    free(data);
}

int aluno_comparator(const void* a,const void* b){
    aluno *aluno1, *aluno2;
    aluno1 = a;
    aluno2 = b; 
    double media1,media2;  
    media1 = (aluno1->p1 + aluno1->p2 + aluno1->p3)/3.0; 
    media2 = (aluno2->p1 + aluno2->p2 + aluno2->p3)/3.0; 
    if(media1<media2){
        return -1;
    }
    else if(media1>media2){
        return 1;
    }
    if(strcmp(aluno1->nome,aluno2->nome) < 0){
        return 1;
    }
    else if(strcmp(aluno1->nome,aluno2->nome) > 0){
        return -1;
    }
    return 0;
}

void* int_constructor(void* data){
    void* ptr = mallocx(sizeof(int));
    memcpy(ptr,data,sizeof(int));
    return ptr;
}

void int_destructor(void* data){
    free (data);
}


int int_comparator(const void* a,const void *b){
    if(*(int*)a < *(int*)b){
        return 1;
    }
    else if( *(int*)a == *(int*)b){
        return 0;
    }
    return -1;
}


int main(void){
    aluno a;
    aluno* aluno_ptr;
    int nro_alunos = 4;
    int i;
    priority_queue_t* pq;
    priority_queue_initialize(&pq,aluno_constructor,aluno_destructor,aluno_comparator);
    for(i=1;i<=nro_alunos;i++){
        printf("Aluno %d\n",i);
        printf("Nome: ");
        scanf("%s",a.nome);
        printf("Nota P1: ");
        scanf("%lf",&a.p1);
        printf("Nota P2" );
        scanf("%lf",&a.p2);
        printf("Nota P3: ");
        scanf("%lf",&a.p3);
        priority_queue_push(pq,&a);
    }

    printf("\n\n");

    while(!priority_queue_empty(pq)){
        aluno_ptr = priority_queue_front(pq);
        printf("Nome: %s\n",aluno_ptr->nome);
        printf("P1: %lf\n",aluno_ptr->p1);
        printf("P2: %lf\n",aluno_ptr->p2);
        printf("P3: %lf\n",aluno_ptr->p3);
        priority_queue_pop(pq);
    }
    priority_queue_delete(&pq);
    return 0;
}



// int main(void){
//     srand(time(NULL));
//     priority_queue_t* pq;
//     priority_queue_initialize(&pq,int_constructor,int_destructor,int_comparator);
//     int i;
//     for(i=0;i<1000;i++){
//         int value = rand()%10000;
//         printf("Inserindo %d na fila de prioridades.\n",value);
//         priority_queue_push(pq,&value);
//     }
//     while(!priority_queue_empty(pq)){
//         int value = * (int*)priority_queue_front(pq);
//         printf("Valor retirado da fila de prioridades: %d\n",value);
//         priority_queue_pop(pq);
//     }
//     priority_queue_delete(&pq);
//     return 0;
// }
