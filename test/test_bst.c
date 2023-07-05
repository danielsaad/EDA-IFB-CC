#include "alloc.h"
#include "bst.h"
#include "check.h"

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

START_TEST(test_bst_find) {
    bst_t *t;
    bst_initialize(&t);
    int i;
    for (i = 0; i < N; i++) {
        bst_insert(t, v[i]);
    }
    for (i = 0; i < N; i++) {
        ck_assert(bst_find(t, v[i]));
    }
    bst_delete(&t);
}
END_TEST

START_TEST(test_bst_remove) {
    bst_t *t;
    bst_initialize(&t);
    int i;
    for (i = 0; i < N; i++) {
        bst_insert(t, v[i]);
    }
    for (i = 0; i < N; i++) {
        ck_assert(bst_find(t, v[i]));
        bst_remove(t, v[i]);
    }
    ck_assert(t->root == NULL);
    bst_delete(&t);
}
END_TEST

START_TEST(test_bst_remove_unique_keys) {
    bst_t *t;
    bst_initialize(&t);
    int i;
    for (i = 0; i < N; i++) {
        bst_insert(t, unique_keys[i]);
    }
    for (i = 0; i < N; i++) {
        ck_assert(bst_find(t, unique_keys[i]));
        bst_remove(t, unique_keys[i]);
        ck_assert(!bst_find(t, unique_keys[i]));
    }
    ck_assert(t->root == NULL);
    bst_delete(&t);
}
END_TEST

Suite *make_bst_suite(void) {
    Suite *s;
    TCase *test_cases;
    s = suite_create("bst");
    test_cases = tcase_create("Core");
    tcase_add_checked_fixture(test_cases, setup, teardown);
    tcase_add_test(test_cases, test_bst_find);
    tcase_add_test(test_cases, test_bst_remove);
    tcase_add_test(test_cases, test_bst_remove_unique_keys);
    suite_add_tcase(s, test_cases);
    return s;
}
