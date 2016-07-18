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
        printf("(%d",*(int*)v->data);
        pre_order(v->left);
        pre_order(v->right);
        printf(" %d)",*(int*)v->data);
    }
}

int main(void){
    int i;
    bst_t* t;
    srand(time(NULL));
    bst_initialize(&t,int_constructor,int_destructor,int_comparator);
    for(i=0;i<10;i++){
        int value = rand()%100;
        printf("Inserindo %d\n",value);
        bst_insert(t,&value);
    }
    pre_order(t->root);
    bst_delete(&t);
    return 0;
}
