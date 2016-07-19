#include <string.h>
#include "check.h"
#include "stack.h"
#include "alloc.h"

static void* int_constructor(void* data){
    void* ptr = mallocx(sizeof(int));
    memcpy(ptr,data,sizeof(int));
    return ptr;
}

static void int_destructor(void* data){
    free(data);
}


START_TEST(test_stack_empty){
    stack_t* s;
    stack_initialize(&s,int_constructor,int_destructor);
    ck_assert_msg(stack_empty(s), "A pilha deve estar vazia após inicialização");
    stack_delete(&s);
}
END_TEST

START_TEST(test_stack_initialization){
    stack_t* s;
    stack_initialize(&s,int_constructor,int_destructor);
    ck_assert(s->size == 0);
    ck_assert(s->top == NULL);
    stack_delete(&s);
}
END_TEST

START_TEST(test_stack_crud){
    stack_t* s;
    const int n = 10000;
    int* v = callocx(n,sizeof(int));
    stack_initialize(&s,int_constructor,int_destructor);
    int i;
    for(i=0;i<n;i++){
        v[i] = rand();
        stack_push(s,&v[i]);
    }
    ck_assert(stack_size(s)==n);
    for(i=n-1; !stack_empty(s) ;i--){
        ck_assert(*(int*) stack_top(s) == v[i]);
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


