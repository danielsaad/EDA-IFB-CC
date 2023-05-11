#include "alloc.h"
#include "dynamic_array.h"
#include <check.h>
#include <stdlib.h>

static const int N = 1000000;

START_TEST(test_dynamic_array_initialize) {
    dynamic_array *arr;
    dynamic_array_initialize(&arr);
    ck_assert(arr->size == 0);
    ck_assert(arr->capacity == 4);
    ck_assert(arr->v != NULL);
    dynamic_array_delete(&arr);
}
END_TEST

START_TEST(test_dynamic_array_delete) {
    dynamic_array *arr;
    dynamic_array_initialize(&arr);
    dynamic_array_delete(&arr);
    ck_assert(arr == NULL);
}
END_TEST

START_TEST(test_dynamic_array_crud) {
    dynamic_array *arr;
    dynamic_array_initialize(&arr);
    int *arr_copy = mallocx(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        int value = rand();
        dynamic_array_push_back(arr, value);
        arr_copy[i] = value;
    }
    ck_assert(dynamic_array_size(arr) == N);
    for (int i = N - 1; i >= 0; i--) {
        ck_assert(dynamic_array_back(arr) == arr_copy[i]);
        dynamic_array_pop_back(arr);
    }
    for (int i = 0; i < N; i++) {
        int value = rand();
        dynamic_array_push_back(arr, value);
        arr_copy[i] = value;
    }
    for (int i = N - 1; i >= 0; i--) {
        ck_assert(dynamic_array_back(arr) == arr_copy[i]);
        dynamic_array_pop_back(arr);
    }
    free(arr_copy);
    dynamic_array_delete(&arr);
}
END_TEST

Suite *make_dynamic_array_suite(void) {
    Suite *s;
    TCase *test_cases;
    s = suite_create("Dynamic Array");
    test_cases = tcase_create("Core");
    tcase_add_test(test_cases, test_dynamic_array_initialize);
    tcase_add_test(test_cases, test_dynamic_array_crud);
    tcase_add_test(test_cases, test_dynamic_array_delete);
    suite_add_tcase(s, test_cases);
    return s;
}
