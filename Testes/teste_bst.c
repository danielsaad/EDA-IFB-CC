#include "check.h"
#include "bst.h"
#include "alloc.h"


static int* v;
static const int N = 10000;

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


static void* int_constructor(void* data){
    void* ptr = mallocx(sizeof(int));
    memcpy(ptr,data,sizeof(int));
    return ptr;
}

static void int_destructor(void* data){
    free(data);
}

static int int_comparator(const void* a,const void* b){
    if(*(int*)a < *(int*) b){
        return -1;
    }
    else if(*(int*)a == *(int*) b){
        return 0;
    }
    return 1;
}




START_TEST(test_bst_find){
    bst_t *t;
    bst_initialize(&t,int_constructor,int_destructor,int_comparator);
    int i;
    for(i=0;i<N;i++){
        bst_insert(t,&v[i]);
    }
    for(i=0;i<N;i++){
        ck_assert(bst_find(t,&v[i]));
    }
    bst_delete(&t);

}
END_TEST

START_TEST(test_bst_remove){
    bst_t *t;
    bst_initialize(&t,int_constructor,int_destructor,int_comparator);
    int i;
    for(i=0;i<N;i++){
        bst_insert(t,&v[i]);
    }
    for(i=0;i<N;i++){
        ck_assert(bst_find(t,&v[i]));
        bst_remove(t,&v[i]);
    }
    bst_delete(&t);

}
END_TEST


Suite* make_bst_suite(void){
    Suite *s;
    TCase *test_cases;
    s = suite_create("BST");
    test_cases = tcase_create("Core");
    tcase_add_checked_fixture(test_cases, setup, teardown);
    tcase_add_test(test_cases, test_bst_find);
    tcase_add_test(test_cases, test_bst_remove);
    suite_add_tcase(s, test_cases);
    return s;
}
