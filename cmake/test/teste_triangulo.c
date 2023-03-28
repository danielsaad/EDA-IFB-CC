#include "check.h"
#include "triangulo.h"

START_TEST(testa_area_triangulo_1){
    triangulo_t t;
    t.a = 3.0;
    t.b = 4.0;
    t.c = 5.0;
    ck_assert(area_triangulo(t)==6.0);
}
END_TEST

START_TEST(testa_area_triangulo_2){
    triangulo_t t;
    t.a = 10.0;
    t.b = 10.0;
    t.c = 12.0;
    ck_assert(area_triangulo(t)==48.0);
}
END_TEST

START_TEST(testa_area_triangulo_3){
    triangulo_t t;
    t.a = 5.0;
    t.b = 5.0;
    t.c = 7.0;
    ck_assert(area_triangulo(t)== 12.497499749949988);
}
END_TEST

Suite* make_triangulo_suite(void){
    Suite *s;
    TCase *test_cases;
    s = suite_create("Triangulo");
    test_cases = tcase_create("Core");
    tcase_add_test(test_cases,testa_area_triangulo_1);
    tcase_add_test(test_cases,testa_area_triangulo_2);
    tcase_add_test(test_cases,testa_area_triangulo_3);
    suite_add_tcase(s, test_cases);
    return s;
}
