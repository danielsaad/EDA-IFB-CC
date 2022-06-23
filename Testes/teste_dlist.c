#include <check.h>
#include "alloc.h"
#include "dlist.h"


static const int N = 10000;
static const int M = 100;
static int* v;

static void* int_constructor(void* data){
    void* ptr = mallocx(sizeof(int));
    memcpy(ptr,data,sizeof(int));
    return ptr;
}

static void int_destructor(void* data){
    free(data);
}


static void setup(void){
    v = callocx(N,sizeof(int));
    int i;
    for(i=0;i<N;i++){
        v[i] = rand();
    }
}

static void teardown(void){
    free(v);
}

START_TEST(test_dlist_empty){
    dlist_t* l;
    dlist_initialize(&l,int_constructor,int_destructor);
    ck_assert(dlist_empty(l));
    dlist_delete(&l);
}
END_TEST



START_TEST(test_dlist_initialization){
    dlist_t* l;
    dlist_initialize(&l,int_constructor,int_destructor);
    ck_assert(dlist_empty(l));
    ck_assert(dlist_size(l)==0);
    ck_assert(l->head == NULL);
    ck_assert(l->tail == NULL);
    ck_assert(l->size == 0);
    dlist_delete(&l);
}
END_TEST


START_TEST(test_dlist_prepend){
    dlist_t* l;
    dlist_initialize(&l,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        dlist_prepend(l,&v[i]);
    }
    ck_assert(dlist_size(l)==N);
    for(i=N-1;!dlist_empty(l);i--){
        ck_assert(*(int*)dlist_access_head(l) == v[i]);
        dlist_remove_head(l);
    }
    dlist_delete(&l);
}
END_TEST


START_TEST(test_dlist_append){
    dlist_t* l;
    dlist_initialize(&l,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        dlist_append(l,&v[i]);
    }
    ck_assert(dlist_size(l)==N);
    for(i=0;!dlist_empty(l);i++){
        ck_assert(*(int*)dlist_access_head(l) == v[i]);
       dlist_remove_head(l);
    }
    dlist_delete(&l);
}
END_TEST


START_TEST(test_dlist_tail){
    dlist_t* l;
    dlist_initialize(&l,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        dlist_append(l,&v[i]);
    }
    ck_assert(dlist_size(l)==N);
    for(i=N-1;!dlist_empty(l);i--){
        ck_assert(*(int*)dlist_access_tail(l) == v[i]);
        dlist_remove_tail(l);
    }
    dlist_delete(&l);
}
END_TEST

START_TEST(test_dlist_access){
    dlist_t* l;
    dlist_initialize(&l,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        dlist_append(l,&v[i]);
    }
    ck_assert(dlist_size(l)==N);
    for(i=0;i<M;i++){
        int k = rand()%dlist_size(l);
        ck_assert(*(int*) dlist_access(l,k)==v[k]);
    }
    dlist_delete(&l);
}
END_TEST


START_TEST(test_dlist_remove_generic_head){
    dlist_t* l;
    dlist_initialize(&l,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        dlist_append(l,&v[i]);
    }
    ck_assert(dlist_size(l)==N);
    for(i=0;!dlist_empty(l);i++){
        ck_assert(*(int*)dlist_access_head(l) == v[i]);
        dlist_remove(l,0);
    }
    dlist_delete(&l);
}
END_TEST


START_TEST(test_dlist_remove_generic_tail){
    dlist_t* l;
    dlist_initialize(&l,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        dlist_append(l,&v[i]);
    }
    ck_assert(dlist_size(l)==N);
    for(i=N-1;!dlist_empty(l);i--){
        ck_assert(*(int*)dlist_access_tail(l) == v[i]);
        dlist_remove(l,dlist_size(l)-1);
    }
    dlist_delete(&l);
}
END_TEST


START_TEST(test_dlist_remove_generic){
    dlist_t* l;
    dlist_initialize(&l,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        dlist_append(l,&v[i]);
    }
    ck_assert(dlist_size(l)==N);
    size_t k =rand()%dlist_size(l);
    dlist_remove(l,k);
    if(k+1<N){
        ck_assert(*(int*)dlist_access(l,k)==v[k+1]);
    }
    if(k>0){
        ck_assert(*(int*)dlist_access(l,k-1)==v[k-1]);
    }
    dlist_delete(&l);
}
END_TEST

Suite* make_dlist_suite(void){
    Suite *s;
    TCase *test_cases;
    s = suite_create("DList");
    test_cases = tcase_create("Core");
    tcase_add_checked_fixture(test_cases, setup, teardown);
    tcase_add_test(test_cases,test_dlist_empty);
    tcase_add_test(test_cases,test_dlist_initialization);
    tcase_add_test(test_cases,test_dlist_prepend);
    tcase_add_test(test_cases,test_dlist_append);
    tcase_add_test(test_cases,test_dlist_tail);
    tcase_add_test(test_cases,test_dlist_access);
    tcase_add_test(test_cases,test_dlist_remove_generic_head);
    tcase_add_test(test_cases,test_dlist_remove_generic_tail);
    tcase_add_test(test_cases,test_dlist_remove_generic);
    suite_add_tcase(s, test_cases);
    return s;
}
