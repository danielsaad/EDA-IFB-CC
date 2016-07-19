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


Suite* stack_suite(void){
    Suite *s;
    TCase *tc_core;
    s = suite_create("Stack");
    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_stack_empty);
    suite_add_tcase(s, tc_core);
    return s;
}


