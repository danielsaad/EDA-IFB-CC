#include "alloc.h"
#include "generic_priority_queue.h"
#include <check.h>
#include <string.h>

static const int N = 10000;

static void *int_constructor(void *data) {
    void *ptr = mallocx(sizeof(int));
    memcpy(ptr, data, sizeof(int));
    return ptr;
}

static void int_destructor(void *data) {
    free(data);
}

static int int_comparator(const void *a, const void *b) {
    const int c = *(const int *)a;
    const int d = *(const int *)b;
    if (c < d) {
        return -1;
    } else if (c == d) {
        return 0;
    }
    return 1;
}

START_TEST(test_generic_priority_queue_empty) {
    generic_priority_queue_t *pq;
    generic_priority_queue_initialize(&pq, int_constructor, int_destructor,
                              int_comparator);
    ck_assert_msg(generic_priority_queue_empty(pq),
                  "A fila de prioridades deve estar vazia após inicialização");
    generic_priority_queue_delete(&pq);
}
END_TEST

START_TEST(test_generic_priority_queue_initialization) {
    generic_priority_queue_t *pq;
    generic_priority_queue_initialize(&pq, int_constructor, int_destructor,
                              int_comparator);
    ck_assert(pq->size == 0);
    ck_assert(pq->data == NULL);
    ck_assert(pq->capacity == 0);
    ck_assert(generic_priority_queue_empty(pq));
    ck_assert(generic_priority_queue_size(pq) == 0);
    generic_priority_queue_delete(&pq);
}
END_TEST

START_TEST(test_generic_priority_queue_crud) {
    generic_priority_queue_t *pq;
    int *v = callocx(N, sizeof(int));
    generic_priority_queue_initialize(&pq, int_constructor, int_destructor,
                              int_comparator);
    int i;
    for (i = 0; i < N; i++) {
        v[i] = rand();
        generic_priority_queue_push(pq, &v[i]);
    }
    qsort(v, N, sizeof(int), int_comparator);
    ck_assert(generic_priority_queue_size(pq) == N);
    for (i = 0; !generic_priority_queue_empty(pq); i++) {
        ck_assert(*(int *)generic_priority_queue_front(pq) == v[N-i-1]);
        generic_priority_queue_pop(pq);
    }
    free(v);
    generic_priority_queue_delete(&pq);
}
END_TEST

Suite *make_generic_priority_queue_suite(void) {
    Suite *s;
    TCase *test_cases;
    s = suite_create("Generic Priority Queue");
    test_cases = tcase_create("Core");
    tcase_add_test(test_cases, test_generic_priority_queue_empty);
    tcase_add_test(test_cases, test_generic_priority_queue_initialization);
    tcase_add_test(test_cases, test_generic_priority_queue_crud);
    suite_add_tcase(s, test_cases);
    return s;
}
