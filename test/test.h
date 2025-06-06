#ifndef TEST_H
#define TEST_H

#include <check.h>

Suite *make_stack_suite(void);
Suite *make_queue_suite(void);
Suite *make_bst_suite(void);
Suite *make_avl_tree_suite(void);
Suite *make_dynamic_array_suite(void);
Suite *make_generic_stack_suite(void);
Suite *make_generic_queue_suite(void);
Suite *make_generic_priority_queue_suite(void);
Suite *make_generic_deque_suite(void);
Suite *make_generic_list_suite(void);
Suite *make_generic_dlist_suite(void);
Suite *make_sorting_suite(void);
Suite *make_generic_bst_suite(void);
Suite *make_generic_avl_tree_suite(void);
Suite *make_treap_suite(void);

#endif