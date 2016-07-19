#include <stdlib.h>
#include <time.h>
#include "check.h"
int main(void){
    srand(time(NULL));
    int number_failed;
    Suite *s;
    SRunner *sr;
    sr = srunner_create(make_stack_suite());
    srunner_add_suite(sr,make_queue_suite());
    srunner_add_suite(sr,make_priority_queue_suite());
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
