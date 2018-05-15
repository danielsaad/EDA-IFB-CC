#include <stdio.h>
#include <string.h>
#include "alloc.h"
#include "list.h"

void* construtor_int(void* data){
    void* ptr = mallocx(sizeof(int));
    memcpy(ptr,data,sizeof(int));
    return ptr;
}

void destrutor_int(void* data){
    free(data);
}

list_node_t* deleta_recursivo_nulos(list_t* lista,list_node_t* node){
    if(node == NULL){
        return NULL;
    }
    list_node_t* aux = node->next;
    if(*(int*)node->data == 0){
        lista->destructor(node->data);
        free(node);
        lista->size--;
        return deleta_recursivo_nulos(lista,aux);
    }
    else{
        node->next = deleta_recursivo_nulos(lista,aux);
        return node;
    }    
}

void deleta_nulos(list_t* lista){
    lista->head = deleta_recursivo_nulos(lista,lista->head);
}

void imprime_lista(list_t* lista){
    list_node_t* ptr = lista->head;
    while(ptr!=NULL){
        printf("%d->",*(int*)ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}
int main(void){
    list_t*  lista;
    list_initialize(&lista,construtor_int,destrutor_int);
    int i;
    int v[7] = {1,0,0,0,1,2,0};
    for(i=0;i<7;i++){
        list_append(lista,&v[i]);
    }
    imprime_lista(lista);
    deleta_nulos(lista);
    imprime_lista(lista);
    list_delete(&lista);
}