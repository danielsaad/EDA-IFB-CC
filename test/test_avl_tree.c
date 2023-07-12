#include "alloc.h"
#include "avl_tree.h"
#include <check.h>

static int *v;
static int *unique_keys;
static const int N = 1000;

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

static int get_height(avl_node_t *v) {
    if (v == NULL) {
        return 0;
    }
    size_t hl, hr;
    hl = get_height(v->left);
    hr = get_height(v->right);
    return hl > hr ? hl + 1 : hr + 1;
}

static int is_balanced(avl_node_t *v) {
    if (v != NULL) {
        size_t hl, hr;
        if (!is_balanced(v->left) || !is_balanced(v->right)) {
            return 0;
        }
        hl = get_height(v->left);
        hr = get_height(v->right);
        if (abs(hl - hr) > 1) {
            return 0;
        }
    }
    return 1;
}

static int has_key_property(avl_tree_t *t, avl_node_t *v) {
    if (v == NULL) {
        return 1;
    }
    if (!has_key_property(t, v->left) || !has_key_property(t, v->right)) {
        return 0;
    }
    if (v->left != NULL && v->left->data > v->data) {
        return 0;
    }
    if (v->right != NULL && v->right->data < v->data) {
        return 0;
    }
    return 1;
}

START_TEST(test_avl_tree_find) {
    avl_tree_t *t;
    avl_tree_initialize(&t);
    int i;
    for (i = 0; i < N; i++) {
        if (!avl_tree_find(t, v[i]))
            avl_tree_insert(t, v[i]);
    }
    for (i = 0; i < N; i++) {
        ck_assert(avl_tree_find(t, v[i]));
    }
    avl_tree_delete(&t);
}
END_TEST

START_TEST(test_avl_balance) {
    avl_tree_t *t;
    avl_tree_initialize(&t);
    int i;
    for (i = 0; i < N; i++) {
        if (!avl_tree_find(t, v[i]))
            avl_tree_insert(t, v[i]);
    }
    ck_assert(is_balanced(t->root));
    avl_tree_delete(&t);
}
END_TEST

START_TEST(test_avl_balance_unique_keys) {
    avl_tree_t *t;
    avl_tree_initialize(&t);
    int i;
    for (i = 0; i < N; i++) {
        avl_tree_insert(t, unique_keys[i]);
    }
    ck_assert(is_balanced(t->root));
    avl_tree_delete(&t);
}
END_TEST

START_TEST(test_avl_key_property) {
    avl_tree_t *t;
    avl_tree_initialize(&t);
    int i;
    for (i = 0; i < N; i++) {
        avl_tree_insert(t, v[i]);
    }
    ck_assert(has_key_property(t, t->root));
    avl_tree_delete(&t);
}
END_TEST

START_TEST(test_avl_key_property_unique_keys) {
    avl_tree_t *t;
    avl_tree_initialize(&t);
    int i;
    for (i = 0; i < N; i++) {
        avl_tree_insert(t, unique_keys[i]);
    }
    ck_assert(has_key_property(t, t->root));
    avl_tree_delete(&t);
}
END_TEST

START_TEST(test_avl_remove) {
    avl_tree_t *t;
    avl_tree_initialize(&t);
    int i;
    for (i = 0; i < N; i++) {
        avl_tree_insert(t, v[i]);
    }
    for (i = 0; i < N; i++) {
        ck_assert(avl_tree_find(t, v[i]));
        avl_tree_remove(t, v[i]);
    }
    ck_assert(t->root == NULL);
    avl_tree_delete(&t);
}
END_TEST

START_TEST(test_avl_remove_unique_keys) {
    avl_tree_t *t;
    avl_tree_initialize(&t);
    int i;
    for (i = 0; i < N; i++) {
        avl_tree_insert(t, unique_keys[i]);
    }
    for (i = 0; i < N; i++) {
        ck_assert(avl_tree_find(t, unique_keys[i]));
        avl_tree_remove(t, unique_keys[i]);
        ck_assert(!avl_tree_find(t, unique_keys[i]));
        ck_assert(is_balanced(t->root));
    }
    ck_assert(t->root == NULL);
    avl_tree_delete(&t);
}
END_TEST

Suite *make_avl_tree_suite(void) {
    Suite *s;
    TCase *test_cases;
    s = suite_create("AVL Tree");
    test_cases = tcase_create("Core");
    tcase_add_checked_fixture(test_cases, setup, teardown);
    tcase_add_test(test_cases, test_avl_tree_find);
    tcase_add_test(test_cases, test_avl_balance);
    tcase_add_test(test_cases, test_avl_balance_unique_keys);
    tcase_add_test(test_cases, test_avl_key_property);
    tcase_add_test(test_cases, test_avl_key_property_unique_keys);
    tcase_add_test(test_cases, test_avl_remove);
    tcase_add_test(test_cases, test_avl_remove_unique_keys);
    suite_add_tcase(s, test_cases);
    return s;
}
