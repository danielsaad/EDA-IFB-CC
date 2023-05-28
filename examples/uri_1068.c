#include <string.h>
#include <stdio.h>
#include "generic_stack.h"
#include "alloc.h"
void* construtor_char(void* data){
    void* ptr = mallocx(sizeof(char));
    memcpy(ptr,data,sizeof(char));
    return ptr;
}

void destrutor_char(void* data){
    free(data);
}

void solve(char* str){
    int i;
    int res = 1;
    generic_stack_t* pilha;
    generic_stack_initialize(&pilha,construtor_char,destrutor_char);
    for(i=0;i<strlen(str);i++){
        char c = str[i];
        if(c=='('){
            generic_stack_push(pilha,&c);
        }
        else if(c==')'){
            if(generic_stack_empty(pilha)){
                res = 0;
                break;
            }
            else{
                generic_stack_pop(pilha);
            }
        }
    }
    if(generic_stack_empty(pilha) && res){
        printf("correct\n");
    }
    else{
        printf("incorrect\n");
    }
    generic_stack_delete(&pilha);
}

int main(void){
    char str[10001];
    while(scanf("%s",str)){
        solve(str);
    }
}