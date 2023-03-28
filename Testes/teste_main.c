#include <check.h>
#include <stdlib.h>
#include <time.h>
#include "test.h"

int main(void){
    srand(time(NULL));
    int number_failed;
    SRunner *sr;
    sr = srunner_create(make_dynamic_array_suite());
    srunner_add_suite(sr,make_stack_suite());    
    srunner_add_suite(sr,make_queue_suite());
    srunner_add_suite(sr,make_priority_queue_suite());
    srunner_add_suite(sr,make_deque_suite());
    srunner_add_suite(sr,make_list_suite());
    srunner_add_suite(sr,make_dlist_suite());
    srunner_add_suite(sr,make_sorting_suite());
    srunner_add_suite(sr,make_bst_suite());
    srunner_add_suite(sr,make_avl_tree_suite());
    srunner_add_suite(sr,make_treap_suite());
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
