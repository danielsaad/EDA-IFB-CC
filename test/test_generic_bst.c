#include "alloc.h"
#include "check.h"
#include "generic_bst.h"

static int *v;
static int *unique_keys;
static const int N = 10000;

static void setup(void) {
    v = callocx(N, sizeof(int));
    unique_keys = callocx(N, sizeof(int));
    int i;
    unique_keys[0] = 0;
    for (i = 0; i < N; i++) {
        v[i] = rand();
    }
    for (i = 0; i < N; i++) {
        int unique;
        do {
            unique_keys[i] = rand();
            int j;
            unique = 1;
            for (j = 0; j < i; j++) {
                if (unique_keys[j] == unique_keys[i]) {
                    unique = 0;
                }
            }
        } while (!unique);
    }
}

static void teardown(void) {
    free(v);
    free(unique_keys);
}

static void *int_constructor(void *data) {
    void *ptr = mallocx(sizeof(int));
    memcpy(ptr, data, sizeof(int));
    return ptr;
}

static void int_destructor(void *data) {
    free(data);
}

static int int_comparator(const void *a, const void *b) {
    if (*(int *)a < *(int *)b) {
        return -1;
    } else if (*(int *)a == *(int *)b) {
        return 0;
    }
    return 1;
}

START_TEST(test_generic_bst_find) {
    generic_bst_t *t;
    generic_bst_initialize(&t, int_constructor, int_destructor, int_comparator);
    int i;
    for (i = 0; i < N; i++) {
        generic_bst_insert(t, &v[i]);
    }
    for (i = 0; i < N; i++) {
        ck_assert(generic_bst_find(t, &v[i]));
    }
    generic_bst_delete(&t);
}
END_TEST

START_TEST(test_generic_bst_remove) {
    generic_bst_t *t;
    generic_bst_initialize(&t, int_constructor, int_destructor, int_comparator);
    int i;
    for (i = 0; i < N; i++) {
        generic_bst_insert(t, &v[i]);
    }
    for (i = 0; i < N; i++) {
        ck_assert(generic_bst_find(t, &v[i]));
        generic_bst_remove(t, &v[i]);
    }
    ck_assert(t->root == NULL);
    generic_bst_delete(&t);
}
END_TEST

START_TEST(test_generic_bst_remove_unique_keys) {
    generic_bst_t *t;
    generic_bst_initialize(&t, int_constructor, int_destructor, int_comparator);
    int i;
    for (i = 0; i < N; i++) {
        generic_bst_insert(t, &unique_keys[i]);
    }
    for (i = 0; i < N; i++) {
        ck_assert(generic_bst_find(t, &unique_keys[i]));
        generic_bst_remove(t, &unique_keys[i]);
        ck_assert(!generic_bst_find(t, &unique_keys[i]));
    }
    ck_assert(t->root == NULL);
    generic_bst_delete(&t);
}
END_TEST

Suite *make_generic_bst_suite(void) {
    Suite *s;
    TCase *test_cases;
    s = suite_create("generic_bst");
    test_cases = tcase_create("Core");
    tcase_add_checked_fixture(test_cases, setup, teardown);
    tcase_add_test(test_cases, test_generic_bst_find);
    tcase_add_test(test_cases, test_generic_bst_remove);
    tcase_add_test(test_cases, test_generic_bst_remove_unique_keys);
    suite_add_tcase(s, test_cases);
    return s;
}
