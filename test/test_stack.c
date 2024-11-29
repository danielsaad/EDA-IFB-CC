#include <string.h>
#include <check.h>
#include "stack.h"
#include "alloc.h"


static const int N = 10000;


START_TEST(test_stack_empty){
    stack_t* s;
    stack_initialize(&s);
    ck_assert_msg(stack_empty(s), "A pilha deve estar vazia após inicialização");
    stack_delete(&s);
}
END_TEST

START_TEST(test_stack_initialization){
    stack_t* s;
    stack_initialize(&s);
    ck_assert(s->size == 0);
    ck_assert(s->capacity == 4);
    stack_delete(&s);
}
END_TEST

START_TEST(test_stack_crud){
    stack_t* s;
    int* v = callocx(N,sizeof(int));
    stack_initialize(&s);
    int i;
    for(i=0;i<N;i++){
        v[i] = rand();
        stack_push(s,v[i]);
    }
    ck_assert(stack_size(s)==N);
    for(i=N-1; !stack_empty(s) ;i--){
        ck_assert(stack_top(s) == v[i]);
        stack_pop(s);
    }
    free(v);
    stack_delete(&s);
}
END_TEST

Suite* make_stack_suite(void){
    Suite *s;
    TCase *test_cases;
    s = suite_create("Stack");
    test_cases = tcase_create("Core");
    tcase_add_test(test_cases, test_stack_empty);
    tcase_add_test(test_cases,test_stack_initialization);
    tcase_add_test(test_cases,test_stack_crud);
    suite_add_tcase(s, test_cases);
    return s;
}


