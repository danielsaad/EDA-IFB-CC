#include <check.h>
#include "alloc.h"
#include "list.h"


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

START_TEST(test_list_empty){
    list_t* l;
    list_initialize(&l,int_constructor,int_destructor);
    ck_assert(list_empty(l));
    list_delete(&l);
}
END_TEST



START_TEST(test_list_initialization){
    list_t* l;
    list_initialize(&l,int_constructor,int_destructor);
    ck_assert(list_empty(l));
    ck_assert(list_size(l)==0);
    ck_assert(l->head == NULL);
    ck_assert(l->tail == NULL);
    ck_assert(l->size == 0);
    list_delete(&l);
}
END_TEST


START_TEST(test_list_prepend){
    list_t* l;
    list_initialize(&l,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        list_prepend(l,&v[i]);
    }
    ck_assert(list_size(l)==N);
    for(i=N-1;!list_empty(l);i--){
        ck_assert(*(int*)list_access_head(l) == v[i]);
        list_remove_head(l);
    }
    list_delete(&l);
}
END_TEST


START_TEST(test_list_append){
    list_t* l;
    list_initialize(&l,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        list_append(l,&v[i]);
    }
    ck_assert(list_size(l)==N);
    for(i=0;!list_empty(l);i++){
        ck_assert(*(int*)list_access_head(l) == v[i]);
        list_remove_head(l);
    }
    list_delete(&l);
}
END_TEST


START_TEST(test_list_tail){
    list_t* l;
    list_initialize(&l,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        list_append(l,&v[i]);
    }
    ck_assert(list_size(l)==N);
    for(i=N-1;!list_empty(l);i--){
        ck_assert(*(int*)list_access_tail(l) == v[i]);
        list_remove_tail(l);
    }
    list_delete(&l);
}
END_TEST

START_TEST(test_list_access){
    list_t* l;
    list_initialize(&l,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        list_append(l,&v[i]);
    }
    ck_assert(list_size(l)==N);
    for(i=0;i<M;i++){
        int k = rand()%list_size(l);
        ck_assert(*(int*) list_access(l,k)==v[k]);
    }
    list_delete(&l);
}
END_TEST


START_TEST(test_list_remove_generic_head){
    list_t* l;
    list_initialize(&l,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        list_append(l,&v[i]);
    }
    ck_assert(list_size(l)==N);
    for(i=0;!list_empty(l);i++){
        ck_assert(*(int*)list_access_head(l) == v[i]);
        list_remove(l,0);
    }
    list_delete(&l);
}
END_TEST


START_TEST(test_list_remove_generic_tail){
    list_t* l;
    list_initialize(&l,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        list_append(l,&v[i]);
    }
    ck_assert(list_size(l)==N);
    for(i=N-1;!list_empty(l);i--){
        ck_assert(*(int*)list_access_tail(l) == v[i]);
        list_remove(l,list_size(l)-1);
    }
    list_delete(&l);
}
END_TEST


START_TEST(test_list_remove_generic){
    list_t* l;
    list_initialize(&l,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        list_append(l,&v[i]);
    }
    ck_assert(list_size(l)==N);
    size_t k =rand()%list_size(l);
    list_remove(l,k);
    if(k+1<N){
        ck_assert(*(int*)list_access(l,k)==v[k+1]);
    }
    if(k>0){
        ck_assert(*(int*)list_access(l,k-1)==v[k-1]);
    }
    list_delete(&l);
}
END_TEST

Suite* make_list_suite(void){
    Suite *s;
    TCase *test_cases;
    s = suite_create("List");
    test_cases = tcase_create("Core");
    tcase_add_checked_fixture(test_cases, setup, teardown);
    tcase_add_test(test_cases,test_list_empty);
    tcase_add_test(test_cases,test_list_initialization);
    tcase_add_test(test_cases,test_list_prepend);
    tcase_add_test(test_cases,test_list_append);
    tcase_add_test(test_cases,test_list_tail);
    tcase_add_test(test_cases,test_list_access);
    tcase_add_test(test_cases,test_list_remove_generic_head);
    tcase_add_test(test_cases,test_list_remove_generic_tail);
    tcase_add_test(test_cases,test_list_remove_generic);
    suite_add_tcase(s, test_cases);
    return s;
}
