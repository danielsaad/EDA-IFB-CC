#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "alloc.h"

typedef struct pessoa{
    char nome[30];
    char cpf[20];
    int idade;
}pessoa;

void* constructor_pessoa(void* data){
    void* ptr = mallocx(sizeof(pessoa));
    memcpy(ptr,data,sizeof(pessoa));
    return ptr;
}

void my_getline(char* str,size_t size){
    int i;
    char c;
    for(i=0;i<size-1;i++){
        c = getchar();
        if(c=='\n'){
            str[i] = '\0';
            break;
        }
        str[i] = c;
    }
    str[size-1]='\0';
    while(c!='\n'){
        c = getchar();
    }
}

void destructor_pessoa(void* data){
    free(data);
}

void cadastra_pessoa(pessoa* p){
    printf("Nome: ");
    my_getline(p->nome,30);
    printf("CPF: ");
    my_getline(p->cpf,20);
    printf("Idade: ");
    scanf("%d%*c",&p->idade);
}

void imprime_pessoa(const pessoa* p){
    printf("Nome: ");
    printf("%s\n",p->nome);
    printf("CPF: ");
    printf("%s\n",p->cpf);
    printf("Idade: ");
    printf("%d\n",p->idade);
}

int main(void){
    int i;
    stack_t* s;
    pessoa p;
    initialize_stack(&s,constructor_pessoa,destructor_pessoa);
    for(i=0;i<5;i++){
        printf("Cadastrando pessoa %d\n",i+1);
        cadastra_pessoa(&p);
        stack_push(s,&p);
    }
    while(!stack_empty(s)){
        printf("\n**Imprimindo pessoa**\n");
        p =  *(pessoa*) stack_top(s);
        stack_pop(s);
        imprime_pessoa(&p);

        printf("\n");
    }
    delete_stack(&s);
    return 0;
}
