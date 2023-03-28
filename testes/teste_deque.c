#include <check.h>
#include "alloc.h"
#include "deque.h"

static const int N = 10000;
static int* v = NULL;

static void* int_constructor(void* data){
    void* ptr = mallocx(sizeof(int));
    memcpy(ptr,data,sizeof(int));
    return ptr;
}

static void int_destructor(void* data){
    free(data);
}

static void setup(void){
    int i;
    v = callocx(N,sizeof(int));
    for(i=0;i<N;i++){
        v[i] = rand();
    }
}

static void teardown(){
    free(v);
}


START_TEST(test_deque_empty){
    deque_t* d;
    deque_initialize(&d,int_constructor,int_destructor);
    ck_assert(deque_empty(d));
    deque_delete(&d);
}
END_TEST

START_TEST(test_deque_initialization){
    deque_t* d;
    deque_initialize(&d,int_constructor,int_destructor);
    ck_assert(deque_empty(d));
    ck_assert(deque_size(d)==0);
    ck_assert(d->size == 0);
    ck_assert(d->front == NULL);
    ck_assert(d->back == NULL);
    deque_delete(&d);
}
END_TEST


START_TEST(test_deque_back){
    deque_t* d;
    deque_initialize(&d,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        deque_push_back(d,&v[i]);
    }
    ck_assert(deque_size(d)==N);
    for(i=N-1;!deque_empty(d);i--){
        ck_assert(*(int*) deque_back(d) == v[i]);
        deque_pop_back(d);
    }
    deque_delete(&d);
}
END_TEST


START_TEST(test_deque_front){
    deque_t* d;
    deque_initialize(&d,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        deque_push_front(d,&v[i]);
    }
    ck_assert(deque_size(d)==N);
    for(i=N-1;!deque_empty(d);i--){
        ck_assert(*(int*) deque_front(d) == v[i]);
        deque_pop_front(d);
    }
    deque_delete(&d);
}
END_TEST


START_TEST(test_deque_back_front){
    deque_t* d;
    deque_initialize(&d,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        deque_push_back(d,&v[i]);
    }
    ck_assert(deque_size(d)==N);
    for(i=0;!deque_empty(d);i++){
        ck_assert(*(int*) deque_front(d) == v[i]);
        deque_pop_front(d);
    }
    deque_delete(&d);
}
END_TEST


START_TEST(test_deque_front_back){
    deque_t* d;
    deque_initialize(&d,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        deque_push_front(d,&v[i]);
    }
    ck_assert(deque_size(d)==N);
    for(i=0;!deque_empty(d);i++){
        ck_assert(*(int*) deque_back(d) == v[i]);
        deque_pop_back(d);
    }
    deque_delete(&d);
}
END_TEST


START_TEST(test_deque_inteleaved){
    deque_t* d;
    deque_initialize(&d,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        if(i%2==0){
            deque_push_front(d,&v[i]);
        }
        else{
            deque_push_back(d,&v[i]);
        }
    }
    ck_assert(deque_size(d)==N);
    for(i=N-1;i>=0 && !deque_empty(d);i--){
        if(i%2==0){
            ck_assert(*(int*) deque_front(d) == v[i]);
            deque_pop_front(d);
        }
    }
    for(i=N-1;!deque_empty(d);i--){
        if(i%2==1){
            ck_assert(*(int*) deque_back(d) == v[i]);
            deque_pop_back(d);
        }
    }
    deque_delete(&d);
}END_TEST


Suite* make_deque_suite(void){
    Suite *s;
    TCase *test_cases;
    s = suite_create("Deque");
    test_cases = tcase_create("Core");
    tcase_add_checked_fixture(test_cases, setup, teardown);
    tcase_add_test(test_cases,test_deque_empty);
    tcase_add_test(test_cases,test_deque_initialization);
    tcase_add_test(test_cases,test_deque_front);
    tcase_add_test(test_cases,test_deque_back);
    tcase_add_test(test_cases,test_deque_back_front);
    tcase_add_test(test_cases,test_deque_front_back);
    tcase_add_test(test_cases,test_deque_inteleaved);
    suite_add_tcase(s, test_cases);
    return s;
}
