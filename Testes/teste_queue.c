#include <string.h>
#include "check.h"
#include "queue.h"
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


START_TEST(test_queue_empty){
    queue_t* q;
    queue_initialize(&q,int_constructor,int_destructor);
    ck_assert_msg(queue_empty(q), "A fila deve estar vazia após inicialização");
    queue_delete(&q);
}
END_TEST

START_TEST(test_queue_initialization){
    queue_t* q;
    queue_initialize(&q,int_constructor,int_destructor);
    ck_assert(q->size == 0);
    ck_assert(q->front == NULL);
    ck_assert(q->back == NULL);
    queue_delete(&q);
}
END_TEST

START_TEST(test_queue_crud){
    queue_t* q;
    int* v = callocx(N,sizeof(int));
    queue_initialize(&q,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        v[i] = rand();
        queue_push(q,&v[i]);
    }
    ck_assert(queue_size(q)==N);
    for(i=0; !queue_empty(q); i++){
        ck_assert(*(int*) queue_front(q) == v[i]);
        queue_pop(q);
    }
    free(v);
    queue_delete(&q);
}
END_TEST

Suite* make_queue_suite(void){
    Suite *s;
    TCase *test_cases;
    s = suite_create("Queue");
    test_cases = tcase_create("Core");
    tcase_add_test(test_cases, test_queue_empty);
    tcase_add_test(test_cases,test_queue_initialization);
    tcase_add_test(test_cases,test_queue_crud);
    suite_add_tcase(s, test_cases);
    return s;
}


