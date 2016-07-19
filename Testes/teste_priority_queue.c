#include <string.h>
#include "check.h"
#include "priority_queue.h"
#include "alloc.h"

static const int N = 10000;


static void* int_constructor(void* data){
    void* ptr = mallocx(sizeof(int));
    memcpy(ptr,data,sizeof(int));
    return ptr;
}

static void int_destructor(void* data){
    free(data);
}

static int int_comparator(void* a,void* b){
    if(*(int*)a < *(int*) b){
        return -1;
    }
    else if(*(int*)a == *(int*) b){
        return 0;
    }
    return 1;
}


START_TEST(test_priority_queue_empty){
    priority_queue_t* pq;
    priority_queue_initialize(&pq,int_constructor,int_destructor,int_comparator);
    ck_assert_msg(priority_queue_empty(pq), "A fila de prioridades deve estar vazia após inicialização");
    priority_queue_delete(&pq);
}
END_TEST

START_TEST(test_priority_queue_initialization){
    priority_queue_t* pq;
    priority_queue_initialize(&pq,int_constructor,int_destructor,int_comparator);
    ck_assert(pq->size == 0);
    ck_assert(pq->data == NULL);
    ck_assert(pq->capacity == 0);
    ck_assert(priority_queue_empty(pq));
    ck_assert(priority_queue_size(pq)==0);
    priority_queue_delete(&pq);
}
END_TEST

START_TEST(test_priority_queue_crud){
    priority_queue_t* pq;
    int* v = callocx(N,sizeof(int));
    priority_queue_initialize(&pq,int_constructor,int_destructor,int_comparator);
    int i;
    for(i=0;i<N;i++){
        v[i] = rand();
        priority_queue_push(pq,&v[i]);
    }
    qsort(v,N,sizeof(int),int_comparator);
    ck_assert(priority_queue_size(pq)==N);
    for(i=0; !priority_queue_empty(pq); i++){
        ck_assert(*(int*) priority_queue_front(pq) == v[i]);
        priority_queue_pop(pq);
    }
    free(v);
    priority_queue_delete(&pq);
}
END_TEST

Suite* make_priority_queue_suite(void){
    Suite *s;
    TCase *test_cases;
    s = suite_create("Queue");
    test_cases = tcase_create("Core");
    tcase_add_test(test_cases, test_priority_queue_empty);
    tcase_add_test(test_cases,test_priority_queue_initialization);
    tcase_add_test(test_cases,test_priority_queue_crud);
    suite_add_tcase(s, test_cases);
    return s;
}


