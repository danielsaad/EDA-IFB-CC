#include "check.h"
#include "quadrado.h"

START_TEST(testa_area_quadrado_1){
    quadrado_t q;
    q.l = 5.0;
    ck_assert(area_quadrado(q)==25.0);
}
END_TEST

START_TEST(testa_area_quadrado_2){
    quadrado_t q;
    q.l = 6.0;
    ck_assert(area_quadrado(q)==36.0);
}
END_TEST

START_TEST(testa_area_quadrado_3){
    quadrado_t q;
    q.l = 1.5;
    ck_assert(area_quadrado(q)==2.25);
}
END_TEST

Suite* make_quadrado_suite(void){
    Suite *s;
    TCase *test_cases;
    s = suite_create("Quadrado");
    test_cases = tcase_create("Core");
    tcase_add_test(test_cases,testa_area_quadrado_1);
    tcase_add_test(test_cases,testa_area_quadrado_2);
    tcase_add_test(test_cases,testa_area_quadrado_3);
    suite_add_tcase(s, test_cases);
    return s;
}
