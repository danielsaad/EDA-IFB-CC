#include <string.h>
#include <check.h>
#include "generic_stack.h"
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


START_TEST(test_generic_stack_empty){
    generic_stack_t* s;
    generic_stack_initialize(&s,int_constructor,int_destructor);
    ck_assert_msg(generic_stack_empty(s), "A pilha deve estar vazia após inicialização");
    generic_stack_delete(&s);
}
END_TEST

START_TEST(test_generic_stack_initialization){
    generic_stack_t* s;
    generic_stack_initialize(&s,int_constructor,int_destructor);
    ck_assert(s->size == 0);
    ck_assert(s->top == NULL);
    generic_stack_delete(&s);
}
END_TEST

START_TEST(test_generic_stack_crud){
    generic_stack_t* s;
    int* v = callocx(N,sizeof(int));
    generic_stack_initialize(&s,int_constructor,int_destructor);
    int i;
    for(i=0;i<N;i++){
        v[i] = rand();
        generic_stack_push(s,&v[i]);
    }
    ck_assert(generic_stack_size(s)==N);
    for(i=N-1; !generic_stack_empty(s) ;i--){
        ck_assert(*(int*) generic_stack_top(s) == v[i]);
        generic_stack_pop(s);
    }
    free(v);
    generic_stack_delete(&s);
}
END_TEST

Suite* make_generic_stack_suite(void){
    Suite *s;
    TCase *test_cases;
    s = suite_create("Stack");
    test_cases = tcase_create("Core");
    tcase_add_test(test_cases, test_generic_stack_empty);
    tcase_add_test(test_cases,test_generic_stack_initialization);
    tcase_add_test(test_cases,test_generic_stack_crud);
    suite_add_tcase(s, test_cases);
    return s;
}


