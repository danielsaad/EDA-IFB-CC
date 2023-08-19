#include <string.h>
#include <stdio.h>
#include <time.h>
#include "bst.h"
#include "queue.h"
#include "alloc.h"


void* int_constructor(void* data){
    void* ptr = mallocx(sizeof(int));
    memcpy(ptr,data,sizeof(int));
    return ptr;
}

void int_destructor(void* data){
    free(data);
}

int int_comparator(const void* a,const void* b){
    if(*(int*)a<*(int*)b){
        return -1;
    }
    else if(*(int*)a==*(int*)b){
        return 0;
    }
    return 1;
}

void pre_order(bst_node_t* v){
    if(v!=NULL){
        printf("%d ",*(int*)v->data);
        pre_order(v->left);
        pre_order(v->right);
    }
}

/**
 * Comandos:
 * i x - insere o inteiro x na rvore
 * r x - remove o inteiro x da árvore
 * f x - procura o inteiro x na árvore
 * p - imprime a árvore em pré-ordem
 * e sai do programa
 */

int main(void){
    bst_t* t;
    char c;
    int i;
    bst_initialize(&t);
    do{
        scanf("%c",&c);
        if(c=='i'){
            scanf("%d",&i);
            bst_insert(t,i);
        }
        else if(c=='r'){
            scanf("%d",&i);
            bst_remove(t,i);
        }
        else if(c=='f'){
            scanf("%d",&i);
            if(bst_find(t,i)){
                printf("%d se encontra na árvore.\n",i);
            }
            else{
                printf("%d NÃO se encontra na árvore.\n",i);
            }
        }
        else if(c=='p'){
            pre_order(t->root);
            printf("\n");
        }
    }while(c!='e');
    bst_delete(&t);
    return 0;
}
