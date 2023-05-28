#include <check.h>
#include "alloc.h"
#include "generic_dlist.h"


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

START_TEST(test_generic_dlist_empty){
    generic_dlist_t* l;
    generic_dlist_initialize(&l,int_constructor,int_destructor);
    ck_assert(generic_dlist_empty(l));
    generic_dlist_delete(&l);
}
END_TEST



START_TEST(test_generic_dlist_initialization){
    generic_dlist_t* l;
    generic_dlist_initialize(&l,int_constructor,int_destructor);
    ck_assert(generic_dlist_empty(l));
    ck_assert(generic_dlist_size(l)==0);
    ck_assert(l->head == NULL);
    ck_assert(l->tail == NULL);
    ck_assert(l->size == 0);
    generic_dlist_delete(&l);
}
END_TEST


START_TEST(test_generic_dlist_prepend){
    generic_dlist_t* l;
    generic_dlist_initialize(&l,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        generic_dlist_prepend(l,&v[i]);
    }
    ck_assert(generic_dlist_size(l)==N);
    for(i=N-1;!generic_dlist_empty(l);i--){
        ck_assert(*(int*)generic_dlist_access_head(l) == v[i]);
        generic_dlist_remove_head(l);
    }
    generic_dlist_delete(&l);
}
END_TEST


START_TEST(test_generic_dlist_append){
    generic_dlist_t* l;
    generic_dlist_initialize(&l,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        generic_dlist_append(l,&v[i]);
    }
    ck_assert(generic_dlist_size(l)==N);
    for(i=0;!generic_dlist_empty(l);i++){
        ck_assert(*(int*)generic_dlist_access_head(l) == v[i]);
        generic_dlist_remove_head(l);
    }
    generic_dlist_delete(&l);
}
END_TEST


START_TEST(test_generic_dlist_tail){
    generic_dlist_t* l;
    generic_dlist_initialize(&l,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        generic_dlist_append(l,&v[i]);
    }
    ck_assert(generic_dlist_size(l)==N);
    for(i=N-1;!generic_dlist_empty(l);i--){
        ck_assert(*(int*)generic_dlist_access_tail(l) == v[i]);
        generic_dlist_remove_tail(l);
    }
    generic_dlist_delete(&l);
}
END_TEST

START_TEST(test_generic_dlist_access){
    generic_dlist_t* l;
    generic_dlist_initialize(&l,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        generic_dlist_append(l,&v[i]);
    }
    ck_assert(generic_dlist_size(l)==N);
    for(i=0;i<M;i++){
        int k = rand()%generic_dlist_size(l);
        ck_assert(*(int*) generic_dlist_access(l,k)==v[k]);
    }
    generic_dlist_delete(&l);
}
END_TEST


START_TEST(test_generic_dlist_remove_generic_head){
    generic_dlist_t* l;
    generic_dlist_initialize(&l,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        generic_dlist_append(l,&v[i]);
    }
    ck_assert(generic_dlist_size(l)==N);
    for(i=0;!generic_dlist_empty(l);i++){
        ck_assert(*(int*)generic_dlist_access_head(l) == v[i]);
        generic_dlist_remove(l,0);
    }
    generic_dlist_delete(&l);
}
END_TEST


START_TEST(test_generic_dlist_remove_generic_tail){
    generic_dlist_t* l;
    generic_dlist_initialize(&l,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        generic_dlist_append(l,&v[i]);
    }
    ck_assert(generic_dlist_size(l)==N);
    for(i=N-1;!generic_dlist_empty(l);i--){
        ck_assert(*(int*)generic_dlist_access_tail(l) == v[i]);
        generic_dlist_remove(l,generic_dlist_size(l)-1);
    }
    generic_dlist_delete(&l);
}
END_TEST


START_TEST(test_generic_dlist_remove_generic){
    generic_dlist_t* l;
    generic_dlist_initialize(&l,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        generic_dlist_append(l,&v[i]);
    }
    ck_assert(generic_dlist_size(l)==N);
    size_t k =rand()%generic_dlist_size(l);
    generic_dlist_remove(l,k);
    if(k+1<N){
        ck_assert(*(int*)generic_dlist_access(l,k)==v[k+1]);
    }
    if(k>0){
        ck_assert(*(int*)generic_dlist_access(l,k-1)==v[k-1]);
    }
    generic_dlist_delete(&l);
}
END_TEST

Suite* make_generic_list_suite(void){
    Suite *s;
    TCase *test_cases;
    s = suite_create("Generic List");
    test_cases = tcase_create("Core");
    tcase_add_checked_fixture(test_cases, setup, teardown);
    tcase_add_test(test_cases,test_generic_dlist_empty);
    tcase_add_test(test_cases,test_generic_dlist_initialization);
    tcase_add_test(test_cases,test_generic_dlist_prepend);
    tcase_add_test(test_cases,test_generic_dlist_append);
    tcase_add_test(test_cases,test_generic_dlist_tail);
    tcase_add_test(test_cases,test_generic_dlist_access);
    tcase_add_test(test_cases,test_generic_dlist_remove_generic_head);
    tcase_add_test(test_cases,test_generic_dlist_remove_generic_tail);
    tcase_add_test(test_cases,test_generic_dlist_remove_generic);
    suite_add_tcase(s, test_cases);
    return s;
}
