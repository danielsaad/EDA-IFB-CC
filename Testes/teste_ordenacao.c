#include "alloc.h"
#include "check.h"
#include "sorting.h"

static int* v;
static const int N = 10000;
static const int M = 1000;


static int is_sorted(const int* v,size_t size){
    size_t i;
    if(size==0)
        return 1;
    for(i=0;i<size-1;i++){
        if(v[i]>v[i+1]){
            return 0;
        }
    }
    return 1;
}

static void setup(void){
    v = callocx(N,sizeof(int));
    int i;
    for(i=0;i<N;i++){
        v[i] = rand() % M;
    }
}

static void teardown(void){
    free(v);
}


START_TEST(test_bubble_sort){
    bubble_sort(v,N);
    ck_assert(is_sorted(v,N));
}
END_TEST


START_TEST(test_inserion_sort){
    insertion_sort(v,N);
    ck_assert(is_sorted(v,N));
}
END_TEST


START_TEST(test_heap_sort){
    heap_sort(v,N);
    ck_assert(is_sorted(v,N));
}
END_TEST


START_TEST(test_quick_sort){
    quick_sort(v,N);
    ck_assert(is_sorted(v,N));
}
END_TEST


START_TEST(test_merge_sort){
    merge_sort(v,N);
    ck_assert(is_sorted(v,N));
}
END_TEST


START_TEST(test_counting_sort){
    counting_sort(v,N);
    ck_assert(is_sorted(v,N));
}
END_TEST


START_TEST(test_radix_sort){
    radix_sort(v,N);
    ck_assert(is_sorted(v,N));
}
END_TEST


Suite* make_sorting_suite(void){
    Suite *s;
    TCase *test_cases;
    s = suite_create("Ordenacao");
    test_cases = tcase_create("Core");
    tcase_add_checked_fixture(test_cases, setup, teardown);
    tcase_add_test(test_cases,test_bubble_sort);
    tcase_add_test(test_cases,test_inserion_sort);
    tcase_add_test(test_cases,test_heap_sort);
    tcase_add_test(test_cases,test_quick_sort);
    tcase_add_test(test_cases,test_merge_sort);
    tcase_add_test(test_cases,test_radix_sort);
    tcase_add_test(test_cases,test_counting_sort);
    suite_add_tcase(s, test_cases);
    return s;
}
