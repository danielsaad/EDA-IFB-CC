#include <string.h>
#include <stdio.h>
#include "list.h"
#include "alloc.h"


void* constructor_int(void* data){
    void* ptr = mallocx(sizeof(int));
    memcpy(ptr,data,sizeof(int));
    return ptr;
}

void destructor_int(void* data){
    free(data);
}

void print_list_int(list_t* l){
    printf("\n");
    list_iterator_t it;
    for(it=l->head;it!=NULL;it=it->next){
        printf("%d -> ",*(int*)it->data);
    }
    printf("NULL\n");
    printf("\n");
}

int main(){
    list_t* l1;
    list_t* l2;
    list_initialize(&l1,constructor_int,destructor_int);
    list_initialize(&l2,constructor_int,destructor_int);
    int i;
    for(i=0;i<10;i++){
        list_append(l1,&i);
        list_prepend(l2,&i);
    }
    print_list_int(l1);
    print_list_int(l2);
    list_delete(&l1);
    list_delete(&l2);
    return 0;
}
